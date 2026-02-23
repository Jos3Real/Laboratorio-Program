#include <iostream>
#include <windows.h> 
#include <iomanip>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string nombre_usuario;
    cout << "Ingrese su nombre: ";
    getline(cin, nombre_usuario);

    cout << "Bienvenido " << nombre_usuario << " a mi programa, donde resuelvo el Ejercicio No. 11";
    
    return 0;
}