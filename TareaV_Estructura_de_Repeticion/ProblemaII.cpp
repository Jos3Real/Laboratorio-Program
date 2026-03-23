#include <iostream>
using namespace std;

int main() {

    int meses, mes_mayor = 0, meses_500 = 0;
    double ahorro, total = 0, promedio, mayor_ahorro = -1;

    cout << "Ingrese la cantidad de meses que desea ahorrar: ";
    cin >> meses;

    if (meses <= 0) {
        cout << "La cantidad de meses debe ser mayor a 0." << endl;
        return 1;
    }

    cout << endl;

    for (int i = 1; i <= meses; i++) {
        cout << "Ingrese lo ahorrado en el mes " << i << ": Q.";
        cin >> ahorro;

        total += ahorro;

        if (ahorro > mayor_ahorro) {
            mayor_ahorro = ahorro;
            mes_mayor = i;
        }

        if (ahorro >= 500) {
            meses_500++;
        }
    }

    promedio = total / meses;

    cout << "\n--- RESUMEN DE AHORRO ---" << endl;
    cout << "Total ahorrado: Q" << total << endl;
    cout << "Promedio mensual: Q" << promedio << endl;
    cout << "Mayor ahorro realizado en el mes: " << mes_mayor << endl;
    cout << "Meses con ahorro de Q500 o mas: " << meses_500 << endl;

    cout << "----------------------------------------" << endl;
    cout << "Estudiante: Jose Daniel Real Garcia" << endl;
    cout << "Carne: 9941-25-837" << endl;
    cout << "----------------------------------------\n" << endl;

    return 0;
}