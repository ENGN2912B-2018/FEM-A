#ifndef ASIANPAYOFF_H
#define ASIANPAYOFF_H

#include <string>
#include <math.h>
#include "Payoff.h"
using namespace std;

class AsianCall : public Payoff {
public:
	// Constructor / Destructor
	AsianCall(const double& strike_price_) : strike_price(strike_price_) {}
	virtual ~AsianCall() {}

	// Call cannot be of negative value, max(average stock price - strike price, 0)
	double operator() (const double& stock_price) const {
		// NOTE: here stock price is the average stock price
		double diff = stock_price - strike_price;
		return (diff > 0.) ? diff : 0.;
	}

	// For the upper bound on the option payoff through time 
	virtual double payoffBound(const double& stock_price, const double& time, const double& interest_rate) {
		// NOTE: here stock price is the average stock price
		double diff = stock_price - (strike_price * exp(-interest_rate * time));
		if (diff < 0) { /* ERROR */ }
		else { return diff; }
	}

	// Print type
	virtual string get_type() { return "Asian Call"; }
 private:
	// Define private variables
	double strike_price;
};

class AsianPut : public Payoff {
public:
	// Constructor / Destructor
	AsianPut(const double& strike_price_) : strike_price(strike_price_) {}
	virtual ~AsianPut() {}

	// Value of a put cannot be negative, max(average strike price - stock_prce, 0)
	double operator() (const double& stock_price) const {
		// NOTE: here stock price is the average stock price
		double diff =  strike_price - stock_price;
		return (diff > 0.) ? diff : 0.;
	}

	// For the lower bound on the option payoff through time 
	virtual double payoffBound(const double& stock_price, const double& time, const double& interest_rate) {
		// NOTE: here stock price is the average stock price
		double diff = (strike_price * exp(-interest_rate * time)) - stock_price;
		if (diff < 0) { /* ERROR */ }
		else { return diff; }
	}

	// Print type
	virtual string get_type() { return "Asian Put"; }
 private:
	// Define private variables
	double strike_price;
};


#endif
