#include <iostream>

int main() {

    using std:: cout;
    using std:: cin;

    cout << "Nombre del estudiante: Jose Daniel Real Garcia\n\n";

    float saldo = 500.0;
    int opcion;
    float monto;

    // Bucle do-while para garantizar que el menu se muestre al menos una vez
    do {
        cout << "\n1. Consultar saldo\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Retirar dinero\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Estructura switch para manejar el menu
        switch (opcion) {
            case 1:
                cout << "Saldo actual: Q" << saldo << "\n";
                break;
            case 2:
                cout << "Ingrese monto a depositar: ";
                cin >> monto;
                if (monto > 0) {
                    saldo += monto;
                    cout << "Deposito realizado correctamente.\n";
                } else {
                    cout << "Monto invalido.\n";
                }
                break;
            case 3:
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                // Validacion de fondos
                if (monto > saldo) {
                    cout << "Fondos insuficientes.\n";
                } else if (monto > 0) {
                    saldo -= monto;
                    cout << "Retiro realizado correctamente.\n";
                } else {
                    cout << "Monto invalido.\n";
                }
                break;
            case 4:
                cout << "Gracias por usar el sistema.\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (opcion != 4); // Repetir hasta que elija 4

    return 0;
}