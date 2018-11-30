#ifndef CONVECTIONDIFFUSIONFEMBASE_H
#define CONVECTIONDIFFUSIONFEMBASE_H

#include <vector>
#include "ConvectionDiffusion.h"
using namespace std;

class ConvectionDiffusionFEMBase {
public:
	// Define solve function to solve for single PDEs in children classes 
	virtual void solve() = 0;

protected:
	// Define protected variable
	ConvectionDiffusionPDE* pde; 
	
	vector<double> x_values; // stores the points on the x dimension
	double h; // x step size 
	double x_bound; // [0,x_right_bound]
	unsigned long N; // number of points for the mesh on the x (spatial) dimension

	double k; // time step size
	double t_bound; // [0, t_upper_bound]
	unsigned long T; // number of points for the mesh on the time dimension
	double current_time; // define the current time
	unsigned long current_t_index; // define the current time index

	double lambda; // k / h
	double sigma; // k / h^2

	vector<vector<double> > solution;
	
	// Constructor / Destructor
	ConvectionDiffusionFEMBase() {}
	ConvectionDiffusionFEMBase(
		double x_bound_,
		double t_bound_,
		unsigned long N_,
		unsigned long T_,
		ConvectionDiffusionPDE* pde_) : 
	x_bound(x_bound_),
	t_bound(t_bound_),
	N(N_), T(T_), pde(pde_) { calculate_step_size(); }
	virtual ~ConvectionDiffusionFEMBase() {}
	
	// Compute the step size function
	void calculate_step_size() {
		h = x_bound / static_cast<double>(N-1);
		k = x_bound / static_cast<double>(T-1);

		lambda = k / h; 
		sigma = k / (h * h); 
		if ((lambda < 1) || (sigma < 1)) { /* ERROR */ }
	}
	
	// Functions to obtain initial/boundary conditions, to be defined in children classes
	virtual void initialize() = 0;
	virtual void calculate_boundary() = 0;

	// Function to obtain solution to system of PDEs, to be defined in children classes
	virtual void calculate_inner_mesh() = 0;
};


#endif
