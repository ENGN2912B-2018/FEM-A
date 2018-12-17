#ifndef ASIANPAYOFF_H
#define ASIANPAYOFF_H

#include <string>
#include <math.h>
#include "Payoff.h"
using namespace std;

class Asian : public Payoff {
public:
	// Constructor / Destructor
	Asian(const double& time_to_expiration_) : time_to_expiration(time_to_expiration_) {}
    ~Asian() {}

	// Call cannot be of negative value, max(current * (1 - average price over current), 0) 
	// - for the sake of the FEM technique we do not multiply by current till the end
    double operator() (const double& avg_price_over_current) const {
		double diff = 1.0 - (avg_price_over_current / time_to_expiration);
		return (diff > 0.) ? diff : 0.;
	}

    double payoffBound(const double& s, const double& t, const double& r) {
        return this->operator()(s);
    }

	// Print type
    string get_type() { return "Asian"; }
 private:
	// Define private variables
	double time_to_expiration;
};


#endif
