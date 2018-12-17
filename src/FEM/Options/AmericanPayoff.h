#ifndef AMERICANPAYOFF_H
#define AMERICANPAYOFF_H

#include <string>
#include <math.h>
#include "Payoff.h"
using namespace std;

class AmericanCall : public Payoff {
public:
	// Constructor / Destructor
	AmericanCall(const double& strike_price_) : strike_price(strike_price_) {}
	virtual ~AmericanCall() {}

	// Call cannot be of negative value, max(stock price - strike price, 0)
	virtual double operator() (const double& stock_price) const {
		double diff = stock_price - strike_price;
		return (diff > 0.) ? diff : 0.;
	}

	// For the upper bound on the option payoff through time 
	virtual double payoffBound(const double& stock_price, const double& time, const double& interest_rate) {
		double diff = stock_price - (strike_price * exp(-interest_rate * time));
		if (diff < 0) { /* ERROR */ }
		else { return diff; }
	}

	// Print type
	virtual string get_type() { return "American Call"; }
 private:
	// Define private variables
	double strike_price;
};

class AmericanPut : public Payoff {
public:
	// Constructor / Destructor
	AmericanPut(const double& strike_price_) : strike_price(strike_price_) {}
	virtual ~AmericanPut() {}

	// Value of a put cannot be negative, max(strike price - stock_prce, 0)
	virtual double operator() (const double& stock_price) const {
		double diff =  strike_price - stock_price;
		return (diff > 0.) ? diff : 0.;
	}

	// For the lower bound on the option payoff through time 
	virtual double payoffBound(const double& stock_price, const double& time, const double& interest_rate) {
		double diff = (strike_price * exp(-interest_rate * time)) - stock_price;
		if (diff < 0) { /* ERROR */ }
		else { return diff; }
	}

	// Print type
	virtual string get_type() { return "American Put"; }
 private:
	// Define private variables
	double strike_price;
};


#endif
