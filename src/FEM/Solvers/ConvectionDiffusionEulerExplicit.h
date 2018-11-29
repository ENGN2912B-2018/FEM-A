#ifndef CONVECTIONDIFFUSIONEULEREXPLICIT_H
#define CONVECTIONDIFFUSIONEULEREXPLICIT_H

#include "ConvectionDiffusionFEMBase.h"

class ConvectionDiffusionEulerExplicit : public ConvectionDiffusionFEMBase {
protected:
	// Define protected variables
	void initialize();
	void calculate_boundary();
	void calculate_inner_mesh();

public:
	// Constructor / Destructor
	ConvectionDiffusionEulerExplicit() {}
	ConvectionDiffusionEulerExplicit(
		double x_bound_,
		double t_bound_,
		unsigned long N_,
		unsigned long T_,
		ConvectionDiffusionPDE* pde_) : ConvectionDiffusionFEMBase(x_bound_,t_bound_,N_,T_,pde_)
	{
		calculate_step_size();
		initialize();
	}
	virtual ~ConvectionDiffusionEulerExplicit() {}
	
	// Solve function
	void solve();
};

#endif
