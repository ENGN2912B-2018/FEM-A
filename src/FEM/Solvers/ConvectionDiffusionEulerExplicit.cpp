#include <vector>
#include "ConvectionDiffusionEulerExplicit.h"

using namespace std;

void ConvectionDiffusionEulerExplicit::initialize() {
	// Initial time conditions
	current_time = 0.0; // time 0 = option expiration - more pos = farther in the past
	current_t_index = 0;

	// Proccessing step
	solution.resize(T);
	for (int t = 0; t < T; t++) { solution[t].resize(N,0.0); }
	x_values.resize(N,0.0);
	
	// Initialize the solution set at all x values
	double x;
	for (unsigned long n = 0; n < N; n++) {
		x = static_cast<double>(n) * h;
		solution[0][n] = pde->initial_condition(x);
		x_values[n] = x;
	}
}


// Compute PDE's boundary conditions
void ConvectionDiffusionEulerExplicit::calculate_boundary() {
	// double time = current_time - k;
	solution[current_t_index][0] = pde->left_boundary(current_time, x_values[0]);
	solution[current_t_index][N-1] = pde->right_boundary(current_time, x_values[N-1]);
}

// Apply FEM to solve system of PDEs with given initial and boundary conditions
void ConvectionDiffusionEulerExplicit::calculate_inner_mesh() {
	double right, center, left, source, x, prev_time = current_time - k;
	double sigma = k / (h * h);
	double lambda = k / h;
	for (unsigned long n = 1; n < N-1; n++) {
		x = x_values[n];

		right = (sigma * pde->diffusion_param(prev_time,x)) 
		+ (0.5 * lambda * pde->convection_param(prev_time,x));

		center = 1.0 - (2.0 * sigma * pde->diffusion_param(prev_time,x))
		+ (k * pde->solution_param(prev_time,x));

		left = (sigma * pde->diffusion_param(prev_time,x))
		- (0.5 * lambda * pde->convection_param(prev_time,x));

		source = k * pde->source_param(prev_time,x);

		solution[current_t_index][n] = (right*solution[current_t_index-1][n+1]) 
		+ (center*solution[current_t_index-1][n]) 
		+ (left*solution[current_t_index-1][n-1]) 
		- source;
	}
}

// Define the solve function for a single PDE
void ConvectionDiffusionEulerExplicit::solve() {
	while (current_time < t_bound) {
		current_time += k;
		current_t_index++;
		calculate_boundary();
		calculate_inner_mesh();
	}
}
