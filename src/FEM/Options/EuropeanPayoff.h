#ifndef EUROPEANPAYOFF_H
#define EUROPEANPAYOFF_H

#include <string>
#include "Payoff.h"
using namespace std;

class EuropeanCall : public Payoff {
public:
	// Constructor / Destructor
	EuropeanCall(const double& strike_price) : strike_price_(strike_price) {}
	virtual ~EuropeanCall() {}

	// Call cannot be of negative value, max(stock price - strike price, 0)
	double operator() (const double& stock_price) const {
		double diff = stock_price - strike_price_;
		return (diff > 0.) ? diff : 0.;
	}
	// Print type
	virtual string get_type() { return "European Call"; }
 private:
	// Define private variables
	double strike_price_;
};

class EuropeanPut : public Payoff {
public:
	// Constructor / Destructor
	EuropeanPut(const double& strike_price) : strike_price_(strike_price) {}
	virtual ~EuropeanPut() {}

	// Value of a put cannot be negative, max(strike price - stock_prce, 0)
	double operator() (const double& stock_price) const {
		double diff =  strike_price_ - stock_price;
		return (diff > 0.) ? diff : 0.;
	}

	// Print type
	virtual string get_type() { return "European Put"; }
 private:
	// Define private variables
	double strike_price_;
};


#endif
