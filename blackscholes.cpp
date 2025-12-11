#include "BlackScholes.h"

//the both following functions will be useful to implement black scholes model

// gaussian cumulative distribution function
double norm_cdf(double x)
{
    return 0.5 * erfc(-x * M_SQRT1_2);
}

//gaussian probability distribution
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





//for the following functions we just write the formulas from the black scholes model for an european option


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
    //we generate a random variable following the gaussian distribution
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);
    double Z = dist(gen);

    //then we write the expression for a spot price at maturity from black scoles model
    return S0 * exp((R - 0.5 * Sigma * Sigma) * T + Sigma * sqrt(T) * Z);
}



vector<double> BlackScholes::simulatePath(double T, int steps, mt19937 &gen)
{
    vector<double> path(steps + 1);
    path[0] = S0;
    double dt = T / steps;

    //same as before, we generate a gaussian
    normal_distribution<> dist(0.0, 1.0);

    //as opposed to the previous function we want an entire path for the spot price
    //so we make a while where at each step we compute a move for the spot price
    //like before the formula for the move comes from black scholes model
    for (int i = 1; i <= steps; i++) {
        double Z = dist(gen);
        path[i] = path[i-1] * exp((R - 0.5 * Sigma * Sigma) * dt + Sigma * sqrt(dt) * Z);
    }
    return path;
}




double BlackScholes::priceMonteCarloAsian(AsianOption* opt, int paths, int steps, mt19937 &gen)
{
    double sum_payoffs = 0.0;
    double T = opt->get_T();

    //we are running a classic Monte Carlo
    //we simulate a path for the spot price steps times
    //at the end of each step we get a possible payoff that we add to sum_payoffs
    for (int i = 0; i < paths; ++i)
    {
        // Pass the generator to simulatePath to ensure the same random numbers are used
        vector<double> path = simulatePath(T, steps, gen);

        double payoff_value = opt->payoff(path);

        sum_payoffs += payoff_value;
    }

    //we compute the average payoff of the previous simulations
    //thus we get a theoretical payoff for our asian option
    double average_payoff = sum_payoffs / paths;

    //we deduce from this theoretical payoff a price for the asian option
    return average_payoff * exp(-R * T);
}




double BlackScholes::replication(Option opt)
{
    double K = opt.get_K();
    double T = opt.get_T();

    //the propotion we want to compute is actually the delta
    //then we just return the delta

    //if it's a call
    if (opt.get_isCall())
    {
        return callDelta(K, T);
    }

    //if it's a put
    else
    {
        return putDelta(K, T);
    }
}


//we use below a simple finite difference to compute the delta (the proportion wanted)

//indeed we recall that the delta is simply the derivative of the option price with respect to the spot price
// as opposed to the european option we don't have an explicit formula for delta
//this the reason why we use finite differences
double BlackScholes::asianReplication(AsianOption* opt, double epsilon, int paths, int steps)
{
    //we save the real S0
    double S0_initial = S0;

    //we create a unique generator for Monte Carlo to use the same random numbers
    //else there will be instability
    mt19937 gen(12345);

    //we price the option
    double V_A_base = priceMonteCarloAsian(opt, paths, steps, gen);

    //we add epsilon to S0 and we reprice the option
    S0 = S0_initial + epsilon;

    //we reset the generator to the same seed to reuse the same paths
    gen.seed(12345);
    double V_A_up = priceMonteCarloAsian(opt, paths, steps, gen);

    //we reassign to S0 its initial value
    S0 = S0_initial;

    //finally we compute the delta
    double delta_asian = (V_A_up - V_A_base) / epsilon;
    return delta_asian;

    //we can notice that we dont need to have two cases (put and call) as in the european option
}






BlackScholes::~BlackScholes() {}
