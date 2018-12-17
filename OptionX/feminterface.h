#ifndef FEMINTERFACE_H
#define FEMINTERFACE_H

#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

vector<vector<double> > solve_problem(
    const double& initial_price,
    const double& volatility,
    const double& risk_free_rate,
    const double& time_till_expiration,
    const string& option_type,
    double price_max = -1,
    int price_steps = -1,
    int time_steps = -1,
    const double& strike_price = -1,
    const double& power = -1,
    const double& lower_barrier = -1,
    const double& upper_barrier = -1,
    const double& rebate = 0);

#endif // FEMINTERFACE_H
