#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include <algorithm>
#include <cmath>
using namespace std;


//European option

class Option
{

private:
    double K; //Strike price
    double T;  // Time to maturity
    bool isCall; //true if it is a call false if it's a put

public:
    //constructors
    Option();
    Option(double K, double T, bool isCall);

    //getters
    double get_K();
    double get_T();
    bool get_isCall();

    //setters
    void set_K(double K);
    void set_T(double T);
    void set_isCall(bool isCall);

    //compute the payoff for a given spot price (at the maturity)
    double payoff(double ST);

    ~Option();


};


#endif // OPTION_H_INCLUDED
