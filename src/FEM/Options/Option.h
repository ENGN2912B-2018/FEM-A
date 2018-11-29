#ifndef OPTION_H
#define OPTION_H

#include "Payoff.h"

class Option {
public:
	// Define public variables
	Payoff* payoff; 
	double strike_price;
	double interest_rate;
	double time_to_expiration;
	double volatility;
	
	// Construct / Destructor
	Option() {}
	~Option() {};
	Option(
		double strike_price_,
		double interest_rate_,
		double time_to_expiration_,
		double volatility_,
		Payoff* payoff_) : 
	strike_price(strike_price_), 
	interest_rate(interest_rate_),
	time_to_expiration(time_to_expiration_),
	volatility(volatility_),
	payoff(payoff_) {}
};




#endif 
