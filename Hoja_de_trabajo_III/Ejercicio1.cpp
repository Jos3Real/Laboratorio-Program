#include <iostream>
using namespace std;

int main (){

    int num;

    cout << " Ingrese un numero entero mayor que 1: ";
    cin >> num;

    while (num <= 1)
    {
        cout << "Error, el número debe ser mayor que 1." << endl;
        cout << "Ingrese un numero enterno mayor que 1: " << endl;
        cin >> num;
    }

    while (num >= 1)
    {
        cout << num << endl;
        num--;
    }
    
    cout << "\nEstudiante: Jose Daniel Real Garcia" << endl << "Carnet: 9941-25-837";

    return 0;
}