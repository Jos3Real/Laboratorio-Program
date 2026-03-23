#include <iostream>
using namespace std;

int main() {

    double nota, suma = 0, promedio;
    int aprobadas = 0, reprobadas = 0;

    for (int i = 1; i <= 5; i++) {
        cout << "Ingrese la nota " << i << " del Estudiante: ";
        cin >> nota;
        
        suma += nota;
        
        if (nota >= 61) {
            aprobadas++;
        } else {
            reprobadas++;
        }
    }

    promedio = suma / 5.0;

    cout << "\n--- RESULTADOS ---" << endl;
    cout << "Suma total: " << suma << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Notas aprobadas: " << aprobadas << endl;
    cout << "Notas reprobadas: " << reprobadas << endl;

    if (promedio >= 61) {
        cout << "Resultado final: El Estudiante Aprueba" << endl;
    } else {
        cout << "Resultado final: El Estudiante Reprueba" << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "Estudiante: Jose Daniel Real Garcia" << endl;
    cout << "Carne: 9941-25-837" << endl;
    cout << "----------------------------------------\n" << endl;

    return 0;
}