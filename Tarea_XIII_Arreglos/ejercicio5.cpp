#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    mostrarEvidencia("Ejercicio 5: Matriz de notas");

    float notas[4][3];
    float promEstudiante[4] = {0};
    float promEvaluacion[3] = {0};

    // Ingreso de datos
    for (int i = 0; i < 4; i++) {
        cout << "--- Estudiante " << (i + 1) << " ---\n";
        for (int j = 0; j < 3; j++) {
            cout << "Nota evaluacion " << (j + 1) << ": ";
            cin >> notas[i][j];
            promEstudiante[i] += notas[i][j];
            promEvaluacion[j] += notas[i][j];
        }
        promEstudiante[i] /= 3.0; // Promedio por estudiante
    }

    // Promedio por evaluación
    for (int j = 0; j < 3; j++) {
        promEvaluacion[j] /= 4.0;
    }

    cout << "\n--- Matriz Completa ---\n";
    for (int i = 0; i < 4; i++) {
        cout << "Estudiante " << (i + 1) << ": ";
        for (int j = 0; j < 3; j++) {
            cout << notas[i][j] << "\t";
        }
        cout << "\n";
    }

    float mejorPromedio = promEstudiante[0];
    int mejorEstudiante = 1;
    cout << "\n--- Promedios por Estudiante ---\n";
    for (int i = 0; i < 4; i++) {
        cout << "Estudiante " << (i + 1) << ": " << promEstudiante[i] << "\n";
        if (promEstudiante[i] > mejorPromedio) {
            mejorPromedio = promEstudiante[i];
            mejorEstudiante = i + 1;
        }
    }

    float peorPromedio = promEvaluacion[0];
    int peorEvaluacion = 1;
    cout << "\n--- Promedios por Evaluacion ---\n";
    for (int j = 0; j < 3; j++) {
        cout << "Evaluacion " << (j + 1) << ": " << promEvaluacion[j] << "\n";
        if (promEvaluacion[j] < peorPromedio) {
            peorPromedio = promEvaluacion[j];
            peorEvaluacion = j + 1;
        }
    }

    cout << "\nEstudiante con mejor promedio: Estudiante " << mejorEstudiante << " (" << mejorPromedio << ")\n";
    cout << "Evaluacion con promedio mas bajo: Evaluacion " << peorEvaluacion << " (" << peorPromedio << ")\n";

    return 0;
}