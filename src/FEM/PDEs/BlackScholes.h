#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

#include <math.h>
#include "ConvectionDiffusion.h"
#include "Option.h"

class BlackScholesPDE : ConvectionDiffusionPDE {
public:
	Option* option; 
	// Constructor / Destructor
	BlackScholesPDE() {}
	BlackScholesPDE(Option* option_) : option(option_) {}
	virtual ~BlackScholesPDE() {}

	// Define parameters for Black Scholes equation
	double source_param(double t, double x) const { return 0.; }
	double solution_param(double t, double x)  const { return -option->interest_rate; }
	double convection_param(double t, double x) const { return option->interest_rate * x; }
	double diffusion_param(double t, double x) const {
		return 0.5 * option->volatility * option->volatility * x * x;
	}

	double left_boundary(double t, double x) const {
		if (option->payoff->get_type() == "European Call") { return 0.0; }
		else { /* Throw Error */ }
	}
	double right_boundary(double t, double x) const {
		if (option->payoff->get_type() == "European Call")
			return x - option->strike_price * exp(-option->interest_rate * (option->time_to_expiration - t));
	}

	double initial_condition(double x) const {
		return option->payoff->operator()(x);
	}
};


#endif
