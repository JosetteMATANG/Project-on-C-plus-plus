#include "BlackScholes.h"


double norm_cdf(double x)
{
    return 0.5 * erfc(-x * M_SQRT1_2);
}

double norm_pdf(double x)
{
    return exp(-0.5 * x * x) / sqrt(2 * M_PI);
}




BlackScholes::BlackScholes()
{
    S0 = 0.0;
    R = 0.0;
    Sigma = 0.0;

}

BlackScholes::BlackScholes(double S0_, double R_, double Sigma_)
{
    S0 = S0_;
    R=R_;
    Sigma= Sigma_;
}




double BlackScholes::get_S0()
{
    return S0;
}
double BlackScholes::get_R()
{
    return R;

}
double BlackScholes::get_Sigma()
{
    return Sigma;
}




void BlackScholes::set_S0(double S0_)
{
    S0 = S0_;
}
void BlackScholes::set_R(double R_)
{
    R=R_;
}
void BlackScholes::set_Sigma(double Sigma_)
{
    Sigma= Sigma_;
}




double BlackScholes::callPrice(double K, double T)
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return S0 * norm_cdf(d1) - K * exp(-R * T) * norm_cdf(d2);
}

double BlackScholes::putPrice(double K, double T)
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return K * exp(-R * T) * norm_cdf(-d2) - S0 * norm_cdf(-d1);
}



double BlackScholes::callDelta(double K, double T)
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    return norm_cdf(d1);
}

double BlackScholes::putDelta(double K, double T)
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    return norm_cdf(d1) - 1.0;
}




double BlackScholes::callGamma(double K, double T) const
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    return norm_pdf(d1) / (S0 * Sigma * sqrt(T));
}

double BlackScholes::putGamma(double K, double T) const
{
    return callGamma(K, T);
}




double BlackScholes::callVega(double K, double T) const
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    return S0 * norm_pdf(d1) * sqrt(T);
}

double BlackScholes::putVega(double K, double T) const
{
    return callVega(K, T);
}






double BlackScholes::callTheta(double K, double T) const
{
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return - (S0 * norm_pdf(d1) * Sigma) / (2 * sqrt(T)) - R * K * exp(-R * T) * norm_cdf(d2);
}
double BlackScholes::putTheta(double K, double T) const {
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return - (S0 * norm_pdf(d1) * Sigma) / (2 * sqrt(T)) + R * K * exp(-R * T) * norm_cdf(-d2);
}






double BlackScholes::callRho(double K, double T) const {
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return K * T * exp(-R * T) * norm_cdf(d2);
}
double BlackScholes::putRho(double K, double T) const {
    double d1 = (log(S0 / K) + (R + 0.5 * Sigma * Sigma) * T) / (Sigma * sqrt(T));
    double d2 = d1 - Sigma * sqrt(T);
    return -K * T * exp(-R * T) * norm_cdf(-d2);
}








double BlackScholes::simulateTerminalPrice(double T) const
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);
    double Z = dist(gen);
    return S0 * exp((R - 0.5 * Sigma * Sigma) * T + Sigma * sqrt(T) * Z);
}



vector<double> BlackScholes::simulatePath(double T, int steps) const
{
    vector<double> path(steps + 1);
    path[0] = S0;
    double dt = T / steps;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);
    for (int i = 1; i <= steps; i++) {
        double Z = dist(gen);
        path[i] = path[i-1] * exp((R - 0.5 * Sigma * Sigma) * dt + Sigma * sqrt(dt) * Z);
    }
    return path;
}




BlackScholes::~BlackScholes() {}
