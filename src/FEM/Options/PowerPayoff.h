#ifndef POWERPAYOFF_H
#define POWERPAYOFF_H

#include <string>
#include <math.h>
#include "Payoff.h"
using namespace std;

class SymmetricPowerCall : public Payoff {
public:
	// Constructor / Destructor
	SymmetricPowerCall(const double& strike_price_, const double& power_) : 
	strike_price(strike_price_), power(power_) {}
	virtual ~SymmetricPowerCall() {}

	// Call cannot be of negative value, max((stock price - strike price)^p, 0)
	double operator() (const double& stock_price) const {
		double diff = pow(stock_price - strike_price, power);
		return (diff > 0.) ? diff : 0.;
	}
	// Print type
	virtual string get_type() { return "Symmetric Power Call"; }
 private:
	// Define private variables
	double strike_price;
	double power;
};

class SymmetricPowerPut : public Payoff {
public:
	// Constructor / Destructor
	SymmetricPowerPut(const double& strike_price_, const double& power_) : 
	strike_price(strike_price_), power(power_) {}
	virtual ~SymmetricPowerPut() {}

	// Value of a put cannot be negative, max(strike price - stock_prce, 0)
	double operator() (const double& stock_price) const {
		double diff =  pow(strike_price - stock_price, power);
		return (diff > 0.) ? diff : 0.;
	}

	// Print type
	virtual string get_type() { return "Symmetric Power Put"; }
 private:
	// Define private variables
	double strike_price;
	double power;
};

class AsymmetricPowerCall : public Payoff {
public:
	// Constructor / Destructor
	AsymmetricPowerCall(const double& strike_price_, const double& power_) : 
	strike_price(strike_price_), power(power_) {}
	virtual ~AsymmetricPowerCall() {}

	// Call cannot be of negative value, max(stock price - strike price, 0)
	double operator() (const double& stock_price) const {
		double diff = pow(stock_price, power) - strike_price;
		return (diff > 0.) ? diff : 0.;
	}
	// Print type
	virtual string get_type() { return "Asymmetric Power Call"; }
 private:
	// Define private variables
	double strike_price;
	double power;
};

class AsymmetricPowerPut : public Payoff {
public:
	// Constructor / Destructor
	AsymmetricPowerPut(const double& strike_price_, const double& power_) : 
	strike_price(strike_price_), power(power_) {}
	virtual ~AsymmetricPowerPut() {}

	// Value of a put cannot be negative, max(strike price - stock_prce, 0)
	double operator() (const double& stock_price) const {
		double diff =  strike_price - pow(stock_price, power);
		return (diff > 0.) ? diff : 0.;
	}

	// Print type
	virtual string get_type() { return "Asymmetric Power Put"; }
 private:
	// Define private variables
	double strike_price;
	double power;
};


#endif
