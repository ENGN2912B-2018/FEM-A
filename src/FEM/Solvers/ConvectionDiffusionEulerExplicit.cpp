#include <vector>
#include "ConvectionDiffusionEulerExplicit.h"

using namespace std;

void ConvectionDiffusionEulerExplicit::initialize() {
	current_time = 0.0;
	current_t_index = 0;

	solution.resize(T);
	for (int t = 0; t < T; t++) { solution[t].resize(N,0.0); }
	x_values.resize(N,0.0);

	double x;
	for (unsigned long n = 0; n < N; n++) {
		x = static_cast<double>(n) * h;
		solution[0][n] = pde->initial_condition(x);
		x_values[n] = x;
	}
}

void ConvectionDiffusionEulerExplicit::calculate_boundary() {
	// double time = current_time - k;
	solution[current_t_index][0] = pde->left_boundary(current_time, x_values[0]);
	solution[current_t_index][N-1] = pde->right_boundary(current_time, x_values[N-1]);
}

void ConvectionDiffusionEulerExplicit::calculate_inner_mesh() {
	double right, center, left, source, x, time = current_time - k;
	double sigma = k / (h * h);
	double lambda = k / h;
	for (unsigned long n = 1; n < N-1; n++) {
		x = x_values[n];

		 right = (sigma * pde->diffusion_param(time,x)) 
		 + (0.5 * lambda * pde->convection_param(time,x));

		 center = 1.0 - (2.0 * sigma * pde->diffusion_param(time,x))
		 + (k * pde->solution_param(time,x));

		 left = (sigma * pde->diffusion_param(time,x))
		 - (0.5 * lambda * pde->convection_param(time,x));

		 source = k * pde->source_param(time,x);

		 solution[current_t_index][n] = (right*solution[current_t_index-1][n+1]) 
		 + (center*solution[current_t_index-1][n]) 
		 + (left*solution[current_t_index-1][n-1]) 
		 - source;
	}
}

void ConvectionDiffusionEulerExplicit::take_step() {
	while (current_time < t_bound) {
		current_time += k;
		current_t_index++;
		calculate_boundary();
		calculate_inner_mesh();
	}
}