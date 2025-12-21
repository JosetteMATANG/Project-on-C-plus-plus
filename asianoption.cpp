#include "AsianOption.h"
#include <algorithm>
#include <numeric>

AsianOption::AsianOption() : Option() {}

AsianOption::AsianOption(double K, double T, bool isCall)
    : Option(K, T, isCall) {}

AsianOption::~AsianOption() {}

//this one wont be used, we only werite it because we have to (heritage)
double AsianOption::payoff(double ST) const {

    if (isCall) return std::max(ST - K, 0.0);
    return std::max(K - ST, 0.0);
}



double AsianOption::payoff(const std::vector<double>& ST_path) const {
    if (ST_path.empty()) return 0.0;


    double sum = std::accumulate(ST_path.begin(), ST_path.end(), 0.0);
    double average = sum / ST_path.size();

    if (isCall) {
        return std::max(average - K, 0.0);
    } else {
        return std::max(K - average, 0.0);
    }
}
