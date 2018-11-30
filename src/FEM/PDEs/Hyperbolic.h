#ifndef HYPERBOLIC_H
#define HYPERBOLIC_H


class HyperbolicPDE {
public:
	// Constructor / Destructor
	HyperbolicPDE() {}
	virtual ~HyperbolicPDE() {}

	// Define these in children function
	virtual double hyperbolic_param(double t, double x) const = 0;
	virtual double hyperbolic_left_boundary(double t, double x, double I) const = 0;
	virtual double hyperbolic_right_boundary(double t, double x, double I) const = 0;
	virtual double init_condition(double x) const = 0;
};



#endif
