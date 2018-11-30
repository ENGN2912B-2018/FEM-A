#ifndef ASIANBLACKSCHOLES_H
#define ASIANBLACKSCHOLES_H

#include <math.h>
#include "ConvectionDiffusion.h"
#include "Hyperbolic.h"
#include "Option.h"

class AsianBlackScholesPDE : ConvectionDiffusionPDE, HyperbolicPDE {
public:
	Option* option; 
	// Constructor / Destructor
	AsianBlackScholesPDE() {}
	AsianBlackScholesPDE(Option* option_) : option(option_) {}
	virtual ~AsianBlackScholesPDE() {}

	// Define parameters for Black Scholes equation
	double source_param(double t, double x) const { return 0.; }
	double solution_param(double t, double x)  const { return -option->interest_rate; }
	double convection_param(double t, double x) const { return option->interest_rate * x; }
	double diffusion_param(double t, double x) const {
		return 0.5 * option->volatility * option->volatility * x * x;
	}

	// Define parameters for the hyperbolic equation
	double hyperbolic_param(double t, double x) const { return x; }

	double hyperbolic_left_boundary(double t, double x, double I) const {
		if (option->payoff->get_type() == "Asian Call") {
			return 0.0;
		} else if (option->payoff->get_type() == "Asian Put") {
			return option->payoff->payoffBound(I, t, option->interest_rate);
		}
	}

	double hyperbolic_right_boundary(double t, double x, double I) const {
		if (option->payoff->get_type() == "Asian Call") {
			return option->payoff->payoffBound(I, t, option->interest_rate);;
		} else if (option->payoff->get_type() == "Asian Put") {
			return 0.0;
		}
	}

	double left_boundary(double t, double x, double I = 0) const {

		if (option->lower_barrier != -1) {
			if (x == option->lower_barrier) { return option->rebate; }
			else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
		} else {
			if (option->payoff->get_type() == "Asian Call") { 
				if (x == 0) { return 0.0; }
				else { /* ERROR */ }
			} else if (option->payoff->get_type() == "Asian Put") {
				return option->payoff->payoffBound(I, t, option->interest_rate);
			}
		}

	}

	double right_boundary(double t, double x, double I = 0) const {

		if (option->upper_barrier != -1) {
			if (x == option->upper_barrier) { return option->rebate; }
			else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
		} else {
			return option->payoff->payoffBound(I, t, option->interest_rate);
		}
	}

	double initial_condition(double x) const {
		return option->payoff->operator()(x);
	}
};


#endif
