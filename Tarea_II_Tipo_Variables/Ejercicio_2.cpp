#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int num1;
    cout << "Ingrese un número entero: ";
    cin >> num1;

    int num2;
    cout << "Ingrese otro número entero: ";
    cin >> num2;

    int suma = num1 + num2;
    int resta = num1 - num2;
    int multiplicacion = num1 * num2;

    cout << "------Resultados de los números ingresados------" << endl;

    cout << "La suma de los números enteros ingresados es: " << suma << endl;
    cout << "La resta de los números enteros ingresados es: " << resta << endl;
    cout << "La multiplicación de los números enteros ingresados es: " << multiplicacion << endl;

    return 0;
}