#include "option.h"

Option::Option()
{
    this->K = 0.0;
    this->T = 0.0;
    this->isCall = true;
}


Option::Option(double K, double T, bool isCall)
{
    this->K = K;
    this->T = T;
    this->isCall = isCall;
}


Option::~Option() {}


double Option::get_K() const
{
    return K;
}


double Option::get_T() const
{
    return T;
}


bool Option::get_isCall() const
{
    return isCall;
}



void Option::set_K(double K)
{
    this->K = K;
}


void Option::set_T(double T)
{
    this->T = T;
}


void Option::set_isCall(bool isCall)
{
    this->isCall = isCall;
}
