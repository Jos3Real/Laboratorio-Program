#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 1: Analisis de temperaturas");

    float temp[7];
    float suma = 0.0, promedio = 0.0;
    float maxTemp, minTemp;

    for (int i = 0; i < 7; i++) {
        cout << "Ingrese la temperatura del dia " << (i + 1) << ": ";
        cin >> temp[i];
        suma += temp[i];

        if (i == 0) {
            maxTemp = temp[0];
            minTemp = temp[0];
        } else {
            if (temp[i] > maxTemp) maxTemp = temp[i];
            if (temp[i] < minTemp) minTemp = temp[i];
        }
    }

    promedio = suma / 7;
    int diasArriba = 0, diasAbajo = 0;

    cout << "\n--- Resultados ---\n";
    cout << "Temperaturas ingresadas: ";
    for (int i = 0; i < 7; i++) {
        cout << temp[i] << " ";
        if (temp[i] > promedio) diasArriba++;
        if (temp[i] < promedio) diasAbajo++;
    }

    cout << "\nTemperatura mas alta: " << maxTemp;
    cout << "\nTemperatura mas baja: " << minTemp;
    cout << "\nPromedio semanal: " << promedio;
    cout << "\nDias arriba del promedio: " << diasArriba;
    cout << "\nDias debajo del promedio: " << diasAbajo << "\n";

    return 0;
}