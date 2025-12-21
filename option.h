#ifndef OPTION_H
#define OPTION_H


#include <algorithm>

class Option {
protected:
    double K;
    double T;
    bool isCall;

public:
    Option();
    Option(double K, double T, bool isCall);
    virtual ~Option();

    double get_K() const;
    double get_T() const;
    bool get_isCall() const;

    void set_K(double K);
    void set_T(double T);
    void set_isCall(bool isCall);

    virtual double payoff(double ST) const = 0;
};

#endif

