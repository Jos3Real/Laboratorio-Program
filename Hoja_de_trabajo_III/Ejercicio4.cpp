#include <iostream>
using namespace std;

int main() {

    int opciones;

    do
    {
        cout <<"\n---MENU---" << endl;
        cout << "1. Mostrar numeros del 1 al 5." << endl;
        cout << "2. Mostrar numeros pares del 1 al 10." << endl;
        cout << "3. Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opciones;

    if (opciones == 1)
    {
        int i = 1;
        while (i <= 5)
        {
            cout << i << " ";
            i++;
        }
        cout << endl;
    }

    else if (opciones == 2)
    {
        int i = 2;
        while (i <= 10)
        {
            cout << i << " ";
            i += 2;
        }
        cout << endl;
    }

    else if (opciones == 3)
    {
        cout << "Saliendo del programa..." << endl;
    }

    else {
        cout << "Opcion Invalida, intente de nuevo." << endl;
    }

    } while (opciones != 3);

    return 0;
}