#include <iostream>
using namespace std;

int main (){

    int num;
    int suma = 0;

    cout << "Ingrese un numero (0 para finalizar el proceso): ";
    cin >> num;

    while (num != 0)
    {
        suma += num;

        cout << "Ingrese otro numero (0 para finalizar el proceso): ";
        cin >> num;
    }
    
    cout << "La suma total es: " << suma << endl;

    cout << "\nEstudiante: Jose Daniel Real Garcia" << endl << "Carnet: 9941-25-837";

    return 0;
}