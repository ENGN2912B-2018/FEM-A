#include <vector>
#include <armadillo>
#include "ConvectionDiffusionEulerImplicit.h"

using namespace std;

void ConvectionDiffusionEulerImplicit::initialize() {
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
void ConvectionDiffusionEulerImplicit::calculate_boundary() {
	// double time = current_time - k;
	solution[current_t_index][0] = pde->left_boundary(current_time, x_values, solution[current_t_index-1],k,h);
	solution[current_t_index][N-1] = pde->right_boundary(current_time, x_values, solution[current_t_index-1],k,h);
}

// Apply FEM to solve system of PDEs with given initial and boundary conditions
void ConvectionDiffusionEulerImplicit::calculate_inner_mesh() {
	double right, center, left, source, x, prev_time = current_time - k;
	double sigma = k / (h * h);
	double lambda = k / h;

	// INIT TRANSITION MATRIX
	arma::mat A = arma::zeros<arma::mat>(N-2,N-2);
	for (unsigned long n = 1; n < N-1; n++) {
		x = x_values[n];

		A(n-1,n-1) = 1.0 
		+ (2.0 * sigma * pde->diffusion_param(current_time,x)) 
		- (k * pde->solution_param(current_time,x));

		if (n < N-2) { 
			A(n-1,n) =  - (sigma * pde->diffusion_param(current_time,x)) 
            - (0.5 * lambda * pde->convection_param(current_time,x));
		} 
        if (n > 1) {
			A(n-1,n-2) = - (sigma * pde->diffusion_param(current_time,x)) 
			+ (0.5 * lambda * pde->convection_param(current_time,x));
		}
	}

	// INIT BOUNDARY VECTOR
	arma::vec b = arma::zeros<arma::vec>(N-2);

	left = - (sigma * pde->diffusion_param(current_time,x_values[0])) + (0.5 * lambda * pde->convection_param(current_time,x_values[0]));
    b(0) = left * pde->left_boundary(current_time, x_values,solution[current_t_index-1],k,h);

	right = - (sigma * pde->diffusion_param(current_time,x_values[N-1])) - (0.5 * lambda * pde->convection_param(current_time,x_values[N-1]));
    b(N-3) = right * pde->right_boundary(current_time, x_values,solution[current_t_index-1],k,h);

	// INIT SOURCE VECTOR
	arma::vec S = arma::zeros<arma::vec>(N-2);
	for (unsigned long n = 1; n < N-1; n++) {
		S(n-1) = k * pde->source_param(current_time,x_values[n]);
	}

	// LAST SOLUTION
	arma::vec u = arma::zeros<arma::vec>(N-2);
	for (unsigned long n = 1; n < N-1; n++) {
        u(n-1) = solution[current_t_index-1][n];
	}

	// SOLVE 
    arma::vec sol = arma::solve(A, u + b + S);

	// STORE
	for (unsigned long n = 1; n < N-1; n++) {
		solution[current_t_index][n] = sol(n-1);
	}
}

// Define the solve function for a single PDE
void ConvectionDiffusionEulerImplicit::solve() {
	while (current_time < t_bound) {
		current_time += k;
		current_t_index++;
		calculate_boundary();
		calculate_inner_mesh();
	}
}
