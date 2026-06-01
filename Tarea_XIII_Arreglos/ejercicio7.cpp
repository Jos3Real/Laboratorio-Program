#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 7: Tablero de posiciones");

    int tablero[5][5] = {0}; // Inicializa toda la matriz en 0
    int fila, columna;

    while (true) {
        cout << "Ingrese fila (0-4): ";
        cin >> fila;
        cout << "Ingrese columna (0-4): ";
        cin >> columna;

        // Validación de rango
        if (fila >= 0 && fila < 5 && columna >= 0 && columna < 5) {
            break;
        } else {
            cout << "Error: Posicion fuera de rango. Intente nuevamente.\n\n";
        }
    }

    tablero[fila][columna] = 1;

    cout << "\nTablero:\n\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}