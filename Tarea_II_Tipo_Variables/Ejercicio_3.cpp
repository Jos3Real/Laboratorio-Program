#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    float estatura;
    cout << "Ingrese su estatura en metros: ";
    cin >> estatura;

    float peso;
    cout << "Ingrese su peso en kilogramos: ";
    cin >> peso;

    float imc = peso / (estatura * estatura);

    cout << "########## Calculadora de IMC ##########" << endl;
    cout << "Su IMC es de: " << imc;

    return 0;
}