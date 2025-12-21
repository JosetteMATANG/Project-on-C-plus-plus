#include "EuropeanOption.h"


EuropeanOption::EuropeanOption() : Option() {}


EuropeanOption::EuropeanOption(double K, double T, bool isCall)
    : Option(K, T, isCall) {}



double EuropeanOption::payoff(double ST) const {
    if (isCall)
    {
        return std::max(ST - K, 0.0);
    }
    else
    {
        return std::max(K - ST, 0.0);
    }
}

EuropeanOption::~EuropeanOption() {}
