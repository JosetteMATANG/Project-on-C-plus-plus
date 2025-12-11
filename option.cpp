#include "option.h"


Option::Option()
{
    K = 0.0;
    T = 0.0;
    isCall = true;
}

Option::Option(double K, double T, bool isCall)
{
    this->K = K;
    this->T = T;
    this->isCall = isCall;
}






double Option::get_K()
{
    return this->K;
}

double Option::get_T()
{
    return this->T;
}

bool Option::get_isCall()
{
    return this->isCall;
}




void Option::set_K(double K)
{
    this->K = K;;
}

void Option::set_T(double T)
{
    this->T = T;
}

void Option::set_isCall(bool isCall)
{
    this->isCall = isCall;
}






double Option::payoff(double ST)
{
        if(this->isCall)
        {
            return max(ST - K, 0.0);
        }

        else
        {
            return max(K - ST, 0.0);
        }
}


Option::~Option(){}
