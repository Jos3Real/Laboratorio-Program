#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int edad;
    cout << "Ingrese su edad: ";
    cin >> edad;

    int edad_futuro = edad + 5;
    cout << "Su edad dentro de 5 años será de: " << edad_futuro << " años." << endl;

    return 0;

}

