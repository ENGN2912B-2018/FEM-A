#ifndef CONVECTIONDIFFUSIONEULEREXPLICIT_H
#define CONVECTIONDIFFUSIONEULEREXPLICIT_H

#include "ConvectionDiffusionFEMBase.h"

class ConvectionDiffusionEulerExplicit : public ConvectionDiffusionFEMBase {
protected:
	void initialize();
	void calculate_boundary();
	void calculate_inner_mesh();

public:
	ConvectionDiffusionEulerExplicit() {}
	ConvectionDiffusionEulerExplicit(
		double x_bound_,
		double t_bound_,
		unsigned long N_,
		unsigned long T_,
		ConvectionDiffusionPDE* pde_) :
	x_bound(x_bound_),
	t_bound(t_bound_),
	N(N_), T(T_), pde(pde_) {
		calculate_step_size();
		initialize();
	}
	virtual ~ConvectionDiffusionEulerExplicit() {}
	
	void take_step();
};

#endif