#ifndef CONVECTIONDIFFUSIONFEMBASE_H
#define CONVECTIONDIFFUSIONFEMBASE_H

#include <vector>
#include "ConvectionDiffusion.h"
using namespace std;

class ConvectionDiffusionFEMBase {
public: 
	virtual void solve() = 0;

protected:
	ConvectionDiffusionPDE* pde; 

	vector<double> x_values; // stores the points on the x dimension
	double h; // x step size 
	double x_bound; // [0,x_right_bound]
	unsigned long N; // number of points for the mesh on the x (spatial) dimension

	double k; // time step size
	double t_bound; // [0, t_upper_bound]
	unsigned long T; // number of points for the mesh on the time dimension
	double current_time;
	unsigned long current_t_index;

	vector<vector<double> > solution;

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
	void calculate_step_size() {
		h = x_bound / static_cast<double>(N-1);
		k = x_bound / static_cast<double>(T-1);
	}

	virtual void initialize() = 0;
	virtual void calculate_boundary() = 0;
	virtual void calculate_inner_mesh() = 0;
};


#endif