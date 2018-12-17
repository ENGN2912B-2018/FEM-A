#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <math.h>
using namespace std;

class DataFrame {
public:
	DataFrame() {}
	DataFrame(const vector<double>& prices_) : past_prices(prices_) {
		calculate_volatility();
	}
	~DataFrame() {}

	void set_prices(const vector<double>& prices_) { 
		past_prices = prices_; 
		calculate_volatility();
	}

	double get_initial_price() {
		return most_recent_price;
	}

	double get_volatility() {
		return annual_volatility;
	}

private:
	vector<double> past_prices;
	double most_recent_price;
	double annual_volatility;

	void calculate_volatility() {
		// Get percent returns
		vector<double> returns(past_prices.size()-1);
		for (int i = 1; i < past_prices.size(); i++) {
			returns[i-1] = (past_prices[i]-past_prices[i-1]) / past_prices[i-1];
		}

		// Get mean of percent returns
		double n = static_cast<double>(past_prices.size());
		double s = 0;
		for (int i = 0; i < past_prices.size(); i++) { 
			s += past_prices[i]; 
		}
		double mean = s / n;

		// Find standard deviation == daily volatility
		s = 0;
		double v; 
		for (int i = 0; i < past_prices.size(); i++) { 
			v = past_prices[i] - mean;
			s += v*v;
		}
		double variance = s / (n-1);
		double std = pow(variance,0.5);

		// Annualize daily vol to get annual vol
		annual_volatility = std * pow(252,0.5);
	}

};



#endif