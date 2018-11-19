#ifndef EUROPEANPAYOFF_H
#define EUROPEANPAYOFF_H

#include <string>
#include "Payoff.h"
using namespace std;

class EuropeanCall : public Payoff {
public:
	EuropeanCall(const double& strike_price) : strike_price_(strike_price) {}
	virtual ~EuropeanCall() {}
	double operator() (const double& stock_price) const {
		double diff = stock_price - strike_price_;
		return (diff > 0.) ? diff : 0.;
	}
	virtual string get_type() { return "European Call"; }
 private:
	double strike_price_;
};

class EuropeanPut : public Payoff {
public:
	string type_ = "European Put";

	EuropeanPut(const double& strike_price) : strike_price_(strike_price) {}
	virtual ~EuropeanPut() {}
	double operator() (const double& stock_price) const {
		double diff =  strike_price_ - stock_price;
		return (diff > 0.) ? diff : 0.;
	}
	virtual string get_type() { return "European Put"; }
 private:
	double strike_price_;
};


#endif