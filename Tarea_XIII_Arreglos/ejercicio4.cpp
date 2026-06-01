#include <iostream>
#include <vector>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 4: Eliminacion logica de datos");

    vector<int> original;
    vector<int> filtrado;
    int num, aEliminar;

    cout << "Ingrese numeros enteros positivos (0 para terminar):\n";
    while (true) {
        cin >> num;
        if (num == 0) break;
        if (num > 0) {
            original.push_back(num);
        }
    }

    cout << "\nVector original:\n";
    for (int i = 0; i < original.size(); i++) {
        cout << original[i] << " ";
    }
    cout << "\n";

    cout << "\nNumero a eliminar: ";
    cin >> aEliminar;

    // Construcción manual del nuevo vector
    for (int i = 0; i < original.size(); i++) {
        if (original[i] != aEliminar) {
            filtrado.push_back(original[i]);
        }
    }

    cout << "\nVector resultante:\n";
    for (int i = 0; i < filtrado.size(); i++) {
        cout << filtrado[i] << " ";
    }
    cout << "\n";

    return 0;
}