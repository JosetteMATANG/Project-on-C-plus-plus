#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include <cmath>
#include <numeric>
#include <algorithm>

#include "option.h"

using namespace std;



class EuropeanOption : public Option
{

public:
    EuropeanOption();
    EuropeanOption(double K, double T, bool isCall);
    virtual ~EuropeanOption();


    double payoff(double ST) const override;


};


#endif // OPTION_H_INCLUDED
