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
	double lower_barrier;
	double upper_barrier;
	double rebate;
	
	// Construct / Destructor
	Option() {}
    ~Option() {}
	Option(
		double strike_price_,
		double interest_rate_,
		double time_to_expiration_,
		double volatility_,
		Payoff* payoff_,
		double lower_barrier_ = -1, // Give option to add barriers - -1 = no barrier
		double upper_barrier_ = -1,
		double rebate_ = 0) : 
	strike_price(strike_price_), 
	interest_rate(interest_rate_),
	time_to_expiration(time_to_expiration_),
	volatility(volatility_),
	payoff(payoff_),
	lower_barrier(lower_barrier_),
	upper_barrier(upper_barrier_),
	rebate(rebate_) {}
};




#endif 
