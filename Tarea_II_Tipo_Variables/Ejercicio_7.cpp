#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char letra;
    cout << "Ingrese una letra: ";
    cin >> letra;

    cout << "La letra que ingreso es: " << letra << endl;
    cout << "La misma letra repetida 3 veces: " << letra << " " << letra << " " << letra << endl;
    cout << "El número que representa internamente es: " << int(letra);

    return 0;
}