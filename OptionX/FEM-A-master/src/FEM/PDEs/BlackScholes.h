#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

#include <math.h>
#include "ConvectionDiffusion.h"
#include "Option.h"

class BlackScholesPDE : public ConvectionDiffusionPDE {
public:
	Option* option; 
	// Constructor / Destructor
	BlackScholesPDE() {}
	BlackScholesPDE(Option* option_) : option(option_) {}
	virtual ~BlackScholesPDE() {}

	// Define parameters for Black Scholes equation
	virtual double source_param(double t, double x) const { return 0.; }
	virtual double solution_param(double t, double x)  const { 
		if (option->payoff->get_type() == "Asian") { return 0.0; }
		else { return -option->interest_rate; }
	}
	virtual double convection_param(double t, double x) const { 
		if (option->payoff->get_type() == "Asian") { return 1 - (option->interest_rate * x); }
		else { return option->interest_rate * x; }
	}
	virtual double diffusion_param(double t, double x) const {
		return 0.5 * option->volatility * option->volatility * x * x;
	}

	virtual double left_boundary(double t, const vector<double>& x_values, const vector<double>& last_solution, const double& k, const double& h) const {

		if (option->payoff->get_type() == "European Call" || 
			option->payoff->get_type() == "Symmetric Power Call" ||
			option->payoff->get_type() == "Asymmetric Power Call" || 
			option->payoff->get_type() == "American Call") {

			double x = x_values[0];
			if (option->lower_barrier != -1) {
				if (x == option->lower_barrier) { return option->rebate; } // If the option has a barrier return the rebate
				else { /* ERROR - lower_barrier >= 0 or lower bound of x has to reach 0 */ }
			} else { 
				if (x == 0) { return 0.0; }
				else { /* ERROR - x must be 0 to be a left boundary */ }
			}

		} else if (option->payoff->get_type() == "European Put" ||
			option->payoff->get_type() == "Symmetric Power Put" ||
			option->payoff->get_type() == "Asymmetric Power Put" || 
			option->payoff->get_type() == "American Put") {

			double x = x_values[0];
			if (option->lower_barrier != -1) {
				if (x == option->lower_barrier) { return option->rebate; }
				else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
			} else {
				return option->payoff->payoffBound(x, t, option->interest_rate);
			}

		} else if (option->payoff->get_type() == "Asian") {
			double c = k / (2.0 * h);
			return ((1.0 - (3.*c)) * last_solution[0]) + (4.0 * c * last_solution[1]) - (c * last_solution[2]);
		}
	}

	virtual double right_boundary(double t, const vector<double>& x_values, const vector<double>& last_solution, const double& k, const double& h) const {

		if (option->payoff->get_type() == "European Call" || 
			option->payoff->get_type() == "Symmetric Power Call" ||
			option->payoff->get_type() == "Asymmetric Power Call" || 
			option->payoff->get_type() == "American Call") {

			double x = x_values[x_values.size()-1];
			if (option->upper_barrier != -1) {
				if (x == option->upper_barrier) { return option->rebate; }
				else { /* ERROR - x must reach high enough such that it is above the upper barrier */ }
			} else {
				return option->payoff->payoffBound(x, t, option->interest_rate);
			}

		} else if (option->payoff->get_type() == "European Put" ||
			option->payoff->get_type() == "Symmetric Power Put" ||
			option->payoff->get_type() == "Asymmetric Power Put" || 
			option->payoff->get_type() == "American Put") {

			double x = x_values[x_values.size()-1];
			if (option->upper_barrier != -1) {
				if (x == option->upper_barrier) { return option->rebate; } // If the option has a barrier return the rebate
				else { /* ERROR - lower_barrier >= 0 or lower bound of x has to reach 0 */ }
			} else { 
				return 0.0;
			}

		} else if (option->payoff->get_type() == "Asian") {
			double x = x_values[x_values.size()-1];
			if (x < option->time_to_expiration) { /* ERROR */ }
			else { return 0.0; } 
		}
	}

	virtual double initial_condition(double x) const {
		return option->payoff->operator()(x);
	}

	virtual double modify_solution(double value, double x) const {
		// Modifies the solution for american options - can only work with Euler Explicit
		if (option->payoff->get_type() == "American Call" || option->payoff->get_type() == "American Put") {
			if (option->payoff->operator()(x) > value) { return option->payoff->operator()(x); }
			else { return value; }
		} else { return value; }
	}
};


#endif
