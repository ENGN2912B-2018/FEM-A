#ifndef CONVECTIONDIFFUSION_H
#define CONVECTIONDIFFUSION_H


class ConvectionDiffusionPDE {
public:
	// Constructor / Destructor
	ConvectionDiffusionPDE() {}
	virtual ~ConvectionDiffusionPDE() {}

	// Define these in children function
	virtual double source_param(double t, double x) const = 0;
	virtual double solution_param(double t, double x) const = 0;
	virtual double convection_param(double t, double x) const = 0;
	virtual double diffusion_param(double t, double x) const = 0;

	virtual double left_boundary(double t, double x) const = 0;
	virtual double right_boundary(double t, double x) const = 0;

	virtual double initial_condition(double x) const = 0;
};



#endif
