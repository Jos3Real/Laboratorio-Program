#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 2: Detector de numeros repetidos");

    int nums[10];
    cout << "Ingrese 10 numeros enteros:\n";
    for (int i = 0; i < 10; i++) {
        cin >> nums[i];
    }

    bool hayRepetidos = false;
    cout << "\nResultados:\n";

    for (int i = 0; i < 10; i++) {
        // Validar si el número actual ya se evaluó antes para no imprimirlo varias veces
        bool yaImpreso = false;
        for (int k = 0; k < i; k++) {
            if (nums[k] == nums[i]) {
                yaImpreso = true;
                break;
            }
        }

        if (!yaImpreso) {
            bool repetidoActual = false;
            // Ciclo anidado para buscar coincidencias adelante
            for (int j = i + 1; j < 10; j++) {
                if (nums[i] == nums[j]) {
                    repetidoActual = true;
                    hayRepetidos = true;
                }
            }
            if (repetidoActual) {
                if (hayRepetidos && i == 0) {
                     cout << "Existen numeros repetidos.\nNumeros repetidos encontrados:\n";
                }
                cout << nums[i] << "\n";
            }
        }
    }

    if (!hayRepetidos) {
        cout << "No existen numeros repetidos.\n";
    }

    return 0;
}