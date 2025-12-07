#ifndef BLACKSCHOLES_H_INCLUDED
#define BLACKSCHOLES_H_INCLUDED

#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
using namespace std;




class BlackScholes {

private:
    double S0;    //Initial spot price
    double R;     //Riskless rate
    double Sigma; //Volatility

public:
    BlackScholes();
    BlackScholes(double S0, double R, double Sigma);



    double get_S0();
    double get_R();
    double get_Sigma();

    void set_S0(double S0);
    void set_R(double R);
    void set_Sigma(double Sigma);



    double callPrice(double K, double T);
    double putPrice(double K, double T);


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



    double simulateTerminalPrice(double T) const;
    vector<double> simulatePath(double T, int steps) const;

    ~BlackScholes();
};

#endif // BLACKSCHOLES_H_INCLUDED
