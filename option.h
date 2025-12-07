#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include <algorithm>
#include <cmath>
using namespace std;
class Option
{

private:
    double K; //Strike price
    double T;  // Time to maturity
    bool isCall;

public:
    Option();
    Option(double K, double T, bool isCall);


    double get_K();
    double get_T();
    bool get_isCall();


    void set_K(double K);
    void set_T(double T);
    void set_isCall(bool isCall);


    double payoff(double ST); //ST is the spot price
    ~Option();


};


#endif // OPTION_H_INCLUDED
