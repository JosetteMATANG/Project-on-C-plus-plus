#include <iostream>
#include <cmath>
#include <random>       // pour mt19937
#include "option.h"
#include "asianoption.h"
#include "blackscholes.h"
using namespace std;

int main()
{
    const double S0 = 120.0;     // Prix initial du sous-jacent
    const double R = 0.03;       // Taux sans risque (3%)
    const double Sigma = 0.25;   // Volatilité (25%)

    // --- 2. PARAMÈTRES DE L'OPTION ASIATIQUE ---
    const double K = 110.0;      // Prix d'exercice
    const double T = 1.5;        // Maturité (1,5 an)
    const bool isCall = true;    // Type d'option (Call)

    // --- 3. PARAMÈTRES MONTE-CARLO ---
    const int paths = 100000;     // Nombre de simulations de chemins
    const int steps = 365;        // Nombre de pas de temps (jours)
    const double epsilon = 0.01;  // Écart pour le calcul du Delta par différences finies

    // --- CONFIGURATION ---
    std::cout << "=== Test du Pricing d'Option Asiatique ===" << std::endl;
    std::cout << "S0: " << S0 << ", R: " << R << ", Sigma: " << Sigma << std::endl;
    std::cout << "K: " << K << ", T: " << T << ", Type: " << (isCall ? "Call" : "Put") << std::endl;
    std::cout << "Monte Carlo (Paths: " << paths << ", Steps: " << steps << ")" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // 1. Instanciation du Modèle de Marché
    BlackScholes bs_model(S0, R, Sigma);

    // 2. Instanciation de l'Option Asiatique
    AsianOption asian_opt(K, T, isCall);

    // 3. Création d'un générateur unique pour le Monte-Carlo
    mt19937 gen(54321); // générateur unique pour CRN

    // 4. Calcul du Prix de l'Option Asiatique (Monte-Carlo)
    double asian_price = bs_model.priceMonteCarloAsian(&asian_opt, paths, steps, gen);

    std::cout << "Prix de l'Option Asiatique: " << asian_price << std::endl;

    // 5. Calcul du Delta (Proportion de Réplication) par Différences Finies
    double asian_delta = bs_model.asianReplication(&asian_opt, epsilon, paths, steps);

    std::cout << "Delta de l'Option Asiatique (Replication): " << asian_delta << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // --- Test option Européenne (pour référence) ---
    std::cout << "=== Référence Option Européenne (Call) ===" << std::endl;
    EuropeanOption european_opt(K, T, isCall);
    double european_price = bs_model.callPrice(K, T);
    double european_delta = bs_model.europeanReplication(european_opt);

    std::cout << "Prix Option Européenne: " << european_price << std::endl;
    std::cout << "Delta Option Européenne: " << european_delta << std::endl;

    return 0;
}
