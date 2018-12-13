#include "AsianPayoff.h"
#include "AmericanPayoff.h"
#include "EuropeanPayoff.h"
#include "PowerPayoff.h"
#include "Option.h"
#include "BlackScholes.h"
#include "ConvectionDiffusionEulerExplicit.h"
#include "ConvectionDiffusionEulerImplicit.h"

#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

vector<vector<double> > solve_problem(
	const double& initial_price, 
	const double& volatility,
	const double& risk_free_rate,
	const double& time_till_expiration,
	const string& option_type,
	double price_max = -1,
	unsigned int price_steps = -1,
	unsigned int time_steps = -1,
	const double& strike_price = -1,
	const double& power = -1,
	const double& lower_barrier = -1,
	const double& upper_barrier = -1,
	const double& rebate = 0) {

	/* ERROR CHECKING */ 
	if (initial_price < 0) { /* initial price must be greater than 0 */}
	else if (volatility < 0) { /* volatility must be greater than 0 */}
	else if (time_till_expiration < 0) { /* time until expiration must be greater than 0 */}
	else if (
	option_type != "Asian" && 
	option_type != "European Call" &&
	option_type != "European Put" &&
	option_type != "Symmetric Power Call" && 
	option_type != "Symmetric Power Put" && 
	option_type != "Asymmetric Power Call" && 
	option_type != "Asymmetric Power Put") { /* time until expiration must be greater than 0 */}
	else if (price_max != -1 || price_max < initial_price) { /* Max price must be greater than initial pirce */ }
	else if (time_steps != -1 || time_steps < 0) { /* time_steps must be greater than 0 */ }
	else if (strike_price != -1 || strike_price < 0) { /* strike_price must be greater than 0 */ }
	else {

		/* Fill in missing */
		if (price_max == -1) {
			if (strike_price != -1) {
				price_max = floor(max(strike_price * 2, initial_price * 2));
			} else  {
				price_max = floor(initial_price * 2);
			}
		}
		if (price_steps == -1) { price_steps = price_max + 1; } 
		if (time_steps == -1) { time_steps = floor(20*time_till_expiration) + 1; }

		/* Define option */
		Payoff* pay_off;
		if (option_type == "Asian") {
			pay_off = new Asian(time_till_expiration);
			price_max = max(2.0 * time_till_expiration,1.0);
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
		} else { /* ERROR */ }
		
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
		double h = price_max / static_cast<double>(price_steps-1);
		double k = time_till_expiration / static_cast<double>(time_steps-1);
		double lambda = k / h;
		double sigma = k / (h * h);
		vector<vector<double> > solution;
		if (option_type != "American Call" || option_type != "American Put") {
			// American options only work with explicit euler

			if (lambda > 2) {
				// Error
			} else if (lambda > 1 || sigma > 0.5) {
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

			if (lambda > 1 || sigma > 0.5) {
				// ERROR
			} else {
				// Excplit Euler
				ConvectionDiffusionEulerExplicit solver(price_max,time_till_expiration,price_steps,time_steps,pde);
				solver.solve();
				solution = solver.getSolution();
			}
		}

		if (option_type == "Asian")
			for (int i = 0; i < solution.size(); i++)
				for (int j = 0; j < solution[i].size(); j++)
					solution[i][j] *= initial_price;

		/* DELETE */ 
		delete pay_off;
		delete option; 
		delete pde;

		return solution;

	}


}