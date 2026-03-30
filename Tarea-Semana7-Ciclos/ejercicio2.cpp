#include <iostream>


int main() {

    using std:: cout;
    using std:: cin;

    cout << "Nombre del estudiante: Jose Daniel Real Garcia\n\n";

    float monto;
    float total_acumulado = 0;
    int cantidad_compras = 0;
    int mayores_iguales_100 = 0;
    int menores_100 = 0;

    cout << "Ingrese los montos de compra. Escriba 0 para finalizar.\n";
    cout << "Entradas:\n";
    cin >> monto;

    // Bucle while para registrar compras hasta ingresar 0
    while (monto != 0) {
        if (monto < 0) {
            // Validacion de datos
            cout << "Monto invalido. Intente nuevamente.\n";
        } else {
            // Acumulacion y conteo
            total_acumulado += monto;
            cantidad_compras++;

            // Clasificacion de compras
            if (monto >= 100) {
                mayores_iguales_100++;
            } else {
                menores_100++;
            }
        }
        cin >> monto; // Leer el siguiente monto
    }

    cout << "\nSalida posible:\n";
    // Comprobar si al menos hay una compra para evitar division por cero
    if (cantidad_compras > 0) {
        float promedio = total_acumulado / cantidad_compras;
        cout << "Total acumulado: Q" << total_acumulado << "\n";
        cout << "Cantidad de compras: " << cantidad_compras << "\n";
        cout << "Promedio de compra: Q" << promedio << "\n";
        cout << "Compras mayores o iguales a Q100: " << mayores_iguales_100 << "\n";
        cout << "Compras menores a Q100: " << menores_100 << "\n";
    } else {
        cout << "No se ingresaron compras validas para calcular.\n";
    }

    return 0;
}