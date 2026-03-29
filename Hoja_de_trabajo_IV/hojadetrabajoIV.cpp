#include <iostream>

int main (){

    using std:: cout;
    using std:: cin;
    using std:: endl;

    int opcion;

    cout << "Nombre: Jose Daniel Real Garcia" << endl;
    cout << "Carne: 9941-25-837" << endl;

    do
    {
        cout << "\n========= MENU =========" << endl;
        cout << "1. Mostrar los numeros del 1 al 5" << endl;
        cout << "2. Mostrar los numeros pares del 2 al 10" << endl;
        cout << "3. Ingresar un numero y mostrar si es positivo, negativo o cero" << endl;
        cout << "4. Salir del menu" << endl;
        cout << "=========================" << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcion;

    if (opcion < 1 || opcion > 4) {
            cout << "Error: Opcion invalida. Por favor, intente de nuevo." << endl;
            continue; 
        }

        switch (opcion) {
            case 1:
                cout << "\n*Opcion 1* Numeros del 1 al 5:" << endl;
                for (int i = 1; i <= 5; i++) {
                    cout << i << " ";
                }
                cout << endl;
                break;

            case 2:
                cout << "\n*Opcion 2* Numeros pares del 2 al 10:" << endl;
                for (int i = 2; i <= 10; i += 2) { 
                    cout << i << " ";
                }
                cout << endl;
                break;

            case 3: {
                double numero;
                cout << "\n*Opcion 3* Ingrese un numero: ";
                cin >> numero;

                if (numero > 0) {
                    cout << "El numero ingresado es POSITIVO." << endl;
                } else if (numero < 0) {
                    cout << "El numero ingresado es NEGATIVO." << endl;
                } else {
                    cout << "El numero ingresado es CERO." << endl;
                }
                break;
            }

            case 4:
                cout << "\nSaliendo del programa..." << endl;
                break;
        }

    } while (opcion != 4);

    return 0;
}