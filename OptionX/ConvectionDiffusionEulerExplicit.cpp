#include <vector>
#include <omp.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include "ConvectionDiffusionEulerExplicit.h"

using namespace std;

void ConvectionDiffusionEulerExplicit::initialize() {
	// Initial time conditions
	current_time = 0.0; // time 0 = option expiration - more pos = farther in the past
	current_t_index = 0;

	// Proccessing step
	solution.resize(T);
    for (unsigned long t = 0; t < T; t++) { solution[t].resize(N,0.0); }
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
	solution[current_t_index][0] = pde->left_boundary(current_time, x_values, solution[current_t_index-1],k,h);
	solution[current_t_index][N-1] = pde->right_boundary(current_time, x_values, solution[current_t_index-1],k,h);
}

// Apply FEM to solve system of PDEs with given initial and boundary conditions
void ConvectionDiffusionEulerExplicit::calculate_inner_mesh() {
	double right, center, left, source, x, value, prev_time = current_time - k;
	#pragma omp parallel for schedule(static) num_threads(4)
	for (unsigned long n = 1; n < N-1; n++) {
		x = x_values[n];

		right = (sigma * pde->diffusion_param(prev_time,x)) 
		+ (0.5 * lambda * pde->convection_param(prev_time,x));

		center = 1.0 - (2.0 * sigma * pde->diffusion_param(prev_time,x))
		+ (k * pde->solution_param(prev_time,x));

		left = (sigma * pde->diffusion_param(prev_time,x))
		- (0.5 * lambda * pde->convection_param(prev_time,x));

		source = k * pde->source_param(prev_time,x);

		value = (right*solution[current_t_index-1][n+1]) 
		+ (center*solution[current_t_index-1][n]) 
		+ (left*solution[current_t_index-1][n-1]) 
		- source;
		
		solution[current_t_index][n] = pde->modify_solution(value,x);
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
