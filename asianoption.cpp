#include "asianoption.h"
#include <numeric>


AsianOption::AsianOption() {}

AsianOption::AsianOption(double K, double T, bool isCall)
{
    this->K = K;
    this->T = T;
    this->isCall = isCall;
}




double AsianOption::get_K()
{
    return this->K;
}

double AsianOption::get_T()
{
    return this->T;
}

bool AsianOption::get_isCall()
{
    return this->isCall;
}




void AsianOption::set_K(double K)
{
    this->K = K;;
}

void AsianOption::set_T(double T)
{
    this->T = T;
}

void AsianOption::set_isCall(bool isCall)
{
    this->isCall = isCall;
}





double AsianOption::payoff(const std::vector<double>& ST_path)
{
    //we compute the average spot price
    double sum_prices = 0.0;

    if (ST_path.empty())
    {
        return 0.0;
    }
    for (double price : ST_path)
    {
        sum_prices += price;
    }

    double avg_price = sum_prices / ST_path.size();


    //we deduce from it the payoff of the asian option

    //if it's a call
    if (this->get_isCall())
    {
        return std::max(avg_price - get_K(), 0.0);
    }

    //if it's a put
    else
    {
        return std::max(get_K() - avg_price, 0.0);
    }
}


AsianOption::~AsianOption() {}
