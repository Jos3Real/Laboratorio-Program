#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 6: Busqueda de un valor en matriz");

    int matriz[3][3];

    cout << "Ingrese los 9 valores enteros para la matriz 3x3:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Fila " << i << ", Columna " << j << ": ";
            cin >> matriz[i][j];
        }
    }

    int buscado;
    cout << "\nNumero buscado: ";
    cin >> buscado;

    bool encontrado = false;
    cout << "\nResultados de busqueda:\n";
    
    // Ciclos anidados para búsqueda
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] == buscado) {
                if (!encontrado) {
                    cout << "El numero aparece en:\n";
                    encontrado = true;
                }
                cout << "Fila " << i << ", columna " << j << "\n";
            }
        }
    }

    if (!encontrado) {
        cout << "El numero no existe en la matriz.\n";
    }

    return 0;
}