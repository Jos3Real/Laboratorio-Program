#include <iostream>
#include <vector>
#include <string>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 3: Lista dinamica de palabras");

    vector<string> palabras;
    string entrada;
    int masDeCinco = 0;
    string masLarga = "", masCorta = "";

    cout << "Ingrese palabras (escriba 'fin' para terminar):\n";

    while (true) {
        cin >> entrada;
        if (entrada == "fin") {
            break;
        }
        palabras.push_back(entrada);
    }

    if (palabras.size() > 0) {
        masLarga = palabras[0];
        masCorta = palabras[0];

        for (int i = 0; i < palabras.size(); i++) {
            if (palabras[i].length() > masLarga.length()) masLarga = palabras[i];
            if (palabras[i].length() < masCorta.length()) masCorta = palabras[i];
            if (palabras[i].length() > 5) masDeCinco++;
        }

        cout << "\n--- Resultados ---\n";
        cout << "Cantidad total de palabras: " << palabras.size() << "\n";
        cout << "Palabra mas larga: " << masLarga << "\n";
        cout << "Palabra mas corta: " << masCorta << "\n";
        cout << "Palabras con mas de 5 letras: " << masDeCinco << "\n";
        
        cout << "Palabras en orden inverso:\n";
        // Ciclo invertido
        for (int i = palabras.size() - 1; i >= 0; i--) {
            cout << palabras[i] << "\n";
        }
    } else {
        cout << "No se ingresaron palabras.\n";
    }

    return 0;
}