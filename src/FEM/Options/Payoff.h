#ifndef PAYOFF_H
#define PAYOFF_H

#include <string>
using namespace std;


class Payoff {
public:
	// Constructor / Destructor
	Payoff() {}; 
	virtual ~Payoff() {}
	// Functions to be defined in children
	virtual double operator() (const double&) const = 0;
	virtual double payoffBound(const double&, const double&, const double&);
	virtual string get_type() = 0;
};


#endif
