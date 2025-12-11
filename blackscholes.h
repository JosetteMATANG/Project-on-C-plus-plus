#ifndef BLACKSCHOLES_H_INCLUDED
#define BLACKSCHOLES_H_INCLUDED

#include <vector>
#include <random>
#include <cmath>
#include <algorithm>


#include "asianoption.h"
#include "option.h"

using namespace std;




class BlackScholes {

private:
    double S0;    //Initial spot price
    double R;     //Riskless rate
    double Sigma; //Volatility

public:

    //constructors
    BlackScholes();
    BlackScholes(double S0, double R, double Sigma);


    //getters
    double get_S0();
    double get_R();
    double get_Sigma();

    //setters
    void set_S0(double S0);
    void set_R(double R);
    void set_Sigma(double Sigma);


    //pricing of a european option
    double callPrice(double K, double T);
    double putPrice(double K, double T);



    //greeks for european options
    //In the case of a european option there is a closed formula for each of them so we compute them directly

    double callDelta(double K, double T);
    double putDelta(double K, double T);



    double callGamma(double K, double T) const;
    double putGamma(double K, double T) const;

    double callVega(double K, double T) const;
    double putVega(double K, double T) const;

    double callTheta(double K, double T) const;
    double putTheta(double K, double T) const;

    double callRho(double K, double T) const;
    double putRho(double K, double T) const;


    //simulation of spot prices, useful for example
    double simulateTerminalPrice(double T) const;  //simulate the spot price at the end of maturity

    // for the the both following functions we have a random number generator
    //it's crucial that this argument is passed for the stability of the monte carlo simulations

    vector<double> simulatePath(double T, int steps, mt19937 &gen); //simulate the spot price path from now to the maturity


    double priceMonteCarloAsian(AsianOption* opt, int paths, int steps, mt19937 &gen);// Monte-Carlo pricing, used for asian options


    //the function below compute the proportion of underlying we must have to delta hedge
    // it returns a double value between -1 and 1

    //we do it here under black scholes model with an european option
    //for instance if it returns 0.8 for each call we must buy 0.8 underlying

    //if it's -0.2 we must short 0.2 underlying for each put
    double replication(Option opt);

    //the same as above but for an asian option
    //we use finite differences
    double asianReplication(AsianOption* opt, double epsilon, int paths, int steps);

    //destructor
    ~BlackScholes();
};

#endif // BLACKSCHOLES_H_INCLUDED
