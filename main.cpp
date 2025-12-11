#include <iostream>
#include <cmath>
#include "option.h"
#include "asianoption.h"
#include "blackscholes.h"
using namespace std;


int main() {

    // -------------------------------
    // Test de l'Option Européenne
    // -------------------------------
    Option euroCall(100.0, 1.0, true);   // K=100, T=1 an, Call
    Option euroPut(100.0, 1.0, false);   // Put

    cout << "=== Test Option Europeenne ===" << endl;
    cout << "Strike: " << euroCall.get_K() << endl;
    cout << "Maturite: " << euroCall.get_T() << endl;

    double ST = 120.0; // prix à maturité

    cout << "Payoff Call (ST=120) : " << euroCall.payoff(ST) << endl;
    cout << "Payoff Put  (ST=120) : " << euroPut.payoff(ST) << endl;


    // -------------------------------
    // Test de l’Option Asiatique
    // -------------------------------
    AsianOption asianCall(100.0, 1.0, true);
    AsianOption asianPut(100.0, 1.0, false);

    cout << "\n=== Test Option Asiatique ===" << endl;

    // Example de chemin
    vector<double> path = {100, 110, 115, 120};

    cout << "Chemin: {100,110,115,120}" << endl;

    cout << "Payoff Asian Call : " << asianCall.payoff(path) << endl;
    cout << "Payoff Asian Put  : " << asianPut.payoff(path) << endl;


    // -------------------------------
    // Test Setters
    // -------------------------------
    cout << "\n=== Test setters ===" << endl;

    euroCall.set_K(150);
    euroCall.set_isCall(false);

    cout << "Nouveau strike : " << euroCall.get_K() << endl;
    cout << "Nouvelle nature (0=put,1=call) : " << euroCall.get_isCall() << endl;

    cout << "Payoff avec ST=120 : " << euroCall.payoff(120) << endl;

    return 0;
}
