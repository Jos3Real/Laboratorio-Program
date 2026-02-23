#include <iostream>
#include <windows.h> 
#include <iomanip>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string nombre_usuario;
    cout << "Ingrese su nombre y su apellido: ";
    getline(cin, nombre_usuario);

    cout << "Nombre Completo: " << nombre_usuario << endl;
    
    string nombres;
    cout << "Ingrese sus nombres: ";
    getline(cin, nombres);

    string apellidos;
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellidos);

    cout << "Nombre Completo: " << nombres << " " << apellidos << endl;

    return 0;
}