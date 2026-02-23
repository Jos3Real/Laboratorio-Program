#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    float base;
    cout << "Ingrese la base de su triangulo en metros: ";
    cin >> base;

    float altura;
    cout << "Ingrese la altura de su triangulo en metros: ";
    cin >> altura;

    float area = (base * altura) / 2;

    cout << "########## Calculadora del Área de un Triangulo ##########" << endl;
    cout << "El Área de su Triangulo es de: " << area << " metros.";

    return 0;
}