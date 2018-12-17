#include "FEMInterface.h"

#include "AsianPayoff.h"
#include "AmericanPayoff.h"
#include "EuropeanPayoff.h"
#include "PowerPayoff.h"
#include "Option.h"
#include "BlackScholes.h"
#include "ConvectionDiffusionEulerExplicit.h"
#include "ConvectionDiffusionEulerImplicit.h"

#include <iostream>
using namespace std;

vector<vector<double> > solve_problem(
	const double& initial_price, 
	const double& volatility,
	const double& risk_free_rate,
	const double& time_till_expiration,
	const string& option_type,
    double price_max, //= -1,
    int price_steps,// = -1,
    int time_steps,// = -1,
    const double& strike_price,// = -1,
    const double& power,// = -1,
    const double& lower_barrier,// = -1,
    const double& upper_barrier,// = -1,
    const double& rebate){// = 0) {

	/* ERROR CHECKING */ 
    if (initial_price < 0) { cout << "initial price must be greater than 0" << endl;}
    else if (volatility < 0) { cout << "volatility must be greater than 0" << endl;}
    else if (time_till_expiration < 0) { cout << "time until expiration must be greater than 0" << endl;}
    else if (
    option_type != "Asian" &&
    option_type != "European Call" &&
    option_type != "European Put" &&
    option_type != "Symmetric Power Call" &&
    option_type != "Symmetric Power Put" &&
    option_type != "Asymmetric Power Call" &&
    option_type != "Asymmetric Power Put" &&
    option_type != "American Call" &&
    option_type != "American Put") { cout << "Option Type not recognized" << endl;}
    else if (price_max != -1 && price_max < initial_price) { cout << "Max price must be greater than initial price" << endl;}
    else if (time_steps != -1 && time_steps < 0) { cout << "time_steps must be greater than 0" << endl;}
    else if (strike_price != -1 && strike_price < 0) { cout << "strike_price must be greater than 0" << endl;}
	else {

		/* Fill in missing */
		if (price_max == -1) {
			if (strike_price != -1) {
				price_max = floor(max(strike_price * 2, initial_price * 2));
			} else  {
				price_max = floor(initial_price * 2);
			}
		}
        if (price_steps == -1) { price_steps = 100 + 1; }
        if (time_steps == -1) { time_steps = ceil(500*time_till_expiration) + 1; }

        if (upper_barrier > price_max) { price_max = upper_barrier; }

		/* Define option */
		Payoff* pay_off;
		if (option_type == "Asian") {
			pay_off = new Asian(time_till_expiration);
            price_max = 2.0 * time_till_expiration;
		} else if (option_type == "European Call") {
			pay_off = new EuropeanCall(strike_price);
		} else if (option_type == "European Put") {
			pay_off = new EuropeanPut(strike_price);
		} else if (option_type == "Symmetric Power Call") {
			pay_off = new SymmetricPowerCall(strike_price,power);
		} else if (option_type == "Symmetric Power Put") {
			pay_off = new SymmetricPowerPut(strike_price,power);
		} else if (option_type == "Asymmetric Power Call") {
			pay_off = new AsymmetricPowerCall(strike_price,power);
		} else if (option_type == "Asymmetric Power Put") {
			pay_off = new AsymmetricPowerPut(strike_price,power);
		} else if (option_type == "American Call") {
			pay_off = new AmericanCall(strike_price);
		} else if (option_type == "American Put") {
			pay_off = new AmericanPut(strike_price);
        } else { cout << "Option type not found" << endl; }
		
		Option* option = new Option(
			strike_price,
			risk_free_rate,
			time_till_expiration,
			volatility,
			pay_off,
			lower_barrier,
			upper_barrier,
			rebate);

		/* PDE */
		BlackScholesPDE* pde = new BlackScholesPDE(option);

		/* PICK SOLVER */
        double a = pde->diffusion_param(0.0, price_max/2.0);
        double eu = pde->convection_param(0.0, price_max/2.0);
        double h = price_max / static_cast<double>(price_steps-1);
        double k = time_till_expiration / static_cast<double>(time_steps-1);

		vector<vector<double> > solution;
		if (option_type != "American Call" || option_type != "American Put") {
			// American options only work with explicit euler

            if (h > (2*a/eu) || k > (h*h/(2*a))) {
				// Implicit Euler
				ConvectionDiffusionEulerImplicit solver(price_max,time_till_expiration,price_steps,time_steps,pde);
				solver.solve();
				solution = solver.getSolution();
			} else {
				// Excplit Euler
				ConvectionDiffusionEulerExplicit solver(price_max,time_till_expiration,price_steps,time_steps,pde);
				solver.solve();
				solution = solver.getSolution();
			}
		} else {

            if (h > (2*a/eu) || k > (h*h/(2*a))) {
                cout << "Adjust Time Steps (increase)" << endl;
			} else {
				// Excplit Euler
				ConvectionDiffusionEulerExplicit solver(price_max,time_till_expiration,price_steps,time_steps,pde);
				solver.solve();
				solution = solver.getSolution();
			}
		}

		if (option_type == "Asian")
            for (unsigned long i = 0; i < solution.size(); i++)
                for (unsigned long j = 0; j < solution[i].size(); j++)
					solution[i][j] *= initial_price;

		/* DELETE */ 
		delete pay_off;
		delete option; 
		delete pde;

		return solution;

	}


}
