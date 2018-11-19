#ifndef PAYOFF_H
#define PAYOFF_H

#include <string>
using namespace std;


class Payoff {
public:
	Payoff() {}; 
	virtual ~Payoff() {}
	virtual double operator() (const double& stock_price) const = 0;
	virtual string get_type() = 0;
};


#endif