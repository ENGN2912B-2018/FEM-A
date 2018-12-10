#ifndef CONVECTIONDIFFUSIONEULEREXPLICIT_H
#define CONVECTIONDIFFUSIONEULEREXPLICIT_H

#include "ConvectionDiffusionFEMBase.h"

class ConvectionDiffusionEulerExplicit : public ConvectionDiffusionFEMBase {
protected:
	// Define protected variables
	virtual void initialize();
	virtual void calculate_boundary();
	virtual void calculate_inner_mesh();

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
		if ((lambda < 1) || (sigma < 0.5)) { /* ERROR */ }
		initialize();
	}
	virtual ~ConvectionDiffusionEulerExplicit() {}
	
	// Solve function
	virtual void solve();
};

#endif
