#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char letra1;
    cout << "Ingrese una letra: ";
    cin >> letra1;

    char letra2;
    cout << "Ingrese otra letra: ";
    cin >> letra2;

    cout << "Ambas letras en una línea: " << letra1 << letra2;
    
    return 0;
}