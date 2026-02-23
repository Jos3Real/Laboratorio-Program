#include <iostream>
#include <windows.h> 
#include <iomanip>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string nombre_usuario;
    cout << "Ingrese su nombre completo: ";
    getline(cin, nombre_usuario);

    int edad;
    cout << "Ingrese su edad: ";
    cin >> edad;

    float altura;
    cout << "Ingrese su altura en metros: ";
    cin >> altura;

    double precio;
    cout << "Ingrese el precio del producto en Quetzales: ";
    cin >> precio;

    char inicial;
    cout << "Ingrese la inicial de su primer apellido: ";
    cin >> inicial;

    cout << "------------------- Resumen de los Datos del Usuario -------------------" << endl;
    cout << "Nombre del Usuario: " << nombre_usuario << endl;
    cout << "Edad del Usuario: " << edad << endl;
    cout << "Altura del Usuario: " << altura << endl;
    cout << "Precio del Producto: Q." << precio << endl;
    cout << "Inicial del Primer Apellido del Usuario: " << inicial << endl;

    return 0;
}