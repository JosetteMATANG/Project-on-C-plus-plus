#include <iostream>
#include <cmath>
#include <random> 

#include "asianoption.h"
#include "europeanoption.h"
#include "option.h"
#include "blackscholes.h"



int main(){

  const int paths = 50000;     // Nombre de simulations de chemins
  const int steps = 252;       // Nombre de pas de temps (ex: jours de trading par an)
  const double epsilon = 0.00001; // Écart pour le calcul du Delta par différences finies

  const double S0 = 100.0;     // Prix initial du sous-jacent
  const double R = 0.05;       // Taux sans risque (5%)
  const double Sigma = 0.20;   // Volatilité (20%)

  std::cout << R"(
     ____        __  _                ____       _               
    / __ \____  / /_(_)___  ____     / __ \_____(_)_______  _____
   / / / / __ \/ __/ / __ \/ __ \   / /_/ / ___/ / ___/ _ \/ ___/
  / /_/ / /_/ / /_/ / /_/ / / / /  / ____/ /  / / /__/  __/ /    
  \____/ .___/\__/_/\____/_/ /_/  /_/   /_/  /_/\___/\___/_/     
      /_/       
  Made by Chakib BOUKHELOUA, Josette Victoire MATANG, and Olivier DE BOISSIEU.
      )" << '\n';
  cout << "Use the pricer to determine the price and delta of financial instruments, using the Black-Scholes model and Monte-Carlo." << endl;
  cout << "Enter the number corresponding to the option type you would like to price:" << endl << "\t 1: European Option" << endl << "\t 2: Asiatic Option" << endl;
  bool option_entered = false;
  int option;
  while (!option_entered) {
    cout << "Number: ";
    cin >> option;

    if (std::cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invalid input: please enter a number (1 or 2).\n";
            continue;
        }

    if (option == 1){
      cout << "European option selected. \n";
      option_entered = true;
      break;
    }
    else if (option == 2)
    {
      cout << "Asiatic option selected. \n";
      option_entered = true;
      break;
    }
    else{
      cout << "Invalid input: Please enter a valid number (1 or 2)." << endl;
    }
    
  }
    double K;      
    double T;        
    bool isCall; 
    cout << "Please enter the strike price: ";
    cin >> K;
    cout << "Please enter the maturity (years): ";
    cin >> T;
    cout << "Please enter 1 if the option is callable, 0 if not: ";
    cin >> isCall;

    // 1. Instanciation du Modèle de Marché
    BlackScholes bs_model(S0, R, Sigma);

    // 2. Création d'un générateur unique pour le Monte-Carlo
    mt19937 gen(12345); // générateur unique pour CRN

    if (option==1) { // European option
      EuropeanOption european_opt(K, T, isCall);
      double european_price = bs_model.callPrice(K, T);
      double european_delta = bs_model.europeanReplication(european_opt);

      cout << "Price of European Option: " << european_price << endl;
      cout << "Delta European Option: " << european_delta << endl;
    }
    else if (option==2) {
      AsianOption asian_opt(K, T, isCall);
      double asian_price = bs_model.priceMonteCarloAsian(&asian_opt, paths, steps, gen);
      double asian_delta = bs_model.asianReplication(&asian_opt, epsilon, paths, steps);

      cout << "Price of Asiatic Option: " << asian_price << endl;
      cout << "Delta Asiatic Option: " << asian_delta << endl;
    }

    return 0;




}
