#ifndef ASIANOPTION_H_INCLUDED
#define ASIANOPTION_H_INCLUDED

#include "Option.h"
#include <vector>
#include <numeric>

class AsianOption : public Option {
public:
    AsianOption();
    AsianOption(double K, double T, bool isCall);
    virtual ~AsianOption();


    double payoff(double ST) const override;


    double payoff(const std::vector<double>& ST_path) const;
};

#endif


