#ifndef ASIANOPTION_H_INCLUDED
#define ASIANOPTION_H_INCLUDED
#include "option.h"
#include <vector>


//Asian Option
class AsianOption
{
private:
    double K; //Strike price
    double T;  // Time to maturity
    bool isCall; //true if it is a call false if it's a put
public:
    //constructors
    AsianOption();
    AsianOption(double K, double T, bool isCall);

    //getters
    double get_K();
    double get_T();
    bool get_isCall();

    //setters
    void set_K(double K);
    void set_T(double T);
    void set_isCall(bool isCall);

    //compute the payoff given a spot price path
    //we recall that ,as opposed to an european option, for an asian option the strike price is compared to the average spot price
    double payoff(const std::vector<double>& ST_path);


    //destructor
    ~AsianOption();
};
#endif // ASIANOPTION_H_INCLUDED


