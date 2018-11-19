#include <vector>
#include "ConvectionDiffusionEulerExplicit.h"

using namespace std;

void ConvectionDiffusionEulerExplicit::initialize() {
	current_time = 0.0;
	current_t = 0;

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
	solution[current_t][0] = pde->left_boundary(current_time, x_values[0]);
	solution[current_t][N-1] = pde->right_boundary(current_time, x_values[N-1]);
}

void ConvectionDiffusionEulerExplicit::calculate_inner_mesh() {
	for (unsigned long n = 1; n < N-1; n++) {
		 
	}
}