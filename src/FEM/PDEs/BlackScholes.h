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

	double left_boundary(double t, double x, double I = 0) const {
		if (option->payoff->get_type() == "European Call" || 
			option->payoff->get_type() == "Symmetric Power Call" ||
			option->payoff->get_type() == "Asymmetric Power Call") {

			if (option->lower_barrier != -1) {
				if (x == option->lower_barrier) { return option->rebate; } // If the option has a barrier return the rebate
				else { /* ERROR - lower_barrier >= 0 or lower bound of x has to reach 0 */ }
			} else { 
				if (x == 0) { return 0.0; }
				else { /* ERROR - x must be 0 to be a left boundary */ }
			}

		} else if (option->payoff->get_type() == "European Put" ||
			option->payoff->get_type() == "Symmetric Power Put" ||
			option->payoff->get_type() == "Asymmetric Power Put") {

			if (option->lower_barrier != -1) {
				if (x == option->lower_barrier) { return option->rebate; }
				else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
			} else {
				return option->payoff->payoffBound(x, t, option->interest_rate);
			}

		}
	}

	double right_boundary(double t, double x, double I = 0) const {
		if (option->payoff->get_type() == "European Call" || 
			option->payoff->get_type() == "Symmetric Power Call" ||
			option->payoff->get_type() == "Asymmetric Power Call") {

			if (option->upper_barrier != -1) {
				if (x == option->upper_barrier) { return option->rebate; }
				else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
			} else {
				return option->payoff->payoffBound(x, t, option->interest_rate);
			}

		} else if (option->payoff->get_type() == "European Put" ||
			option->payoff->get_type() == "Symmetric Power Put" ||
			option->payoff->get_type() == "Asymmetric Power Put") {

			if (option->upper_barrier != -1) {
				if (x == option->upper_barrier) { return option->rebate; } // If the option has a barrier return the rebate
				else { /* ERROR - lower_barrier >= 0 or lower bound of x has to reach 0 */ }
			} else { 
				return 0.0;
			}

		}
	}

	double initial_condition(double x) const {
		return option->payoff->operator()(x);
	}
};


#endif
