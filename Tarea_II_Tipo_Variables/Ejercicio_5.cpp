#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    double precio;
    cout << "Ingrese el precio del Producto en Quetzales: ";
    cin >> precio;
    
    double cantidad;
    cout << "Ingrese la cantidad de Productos que comprara: ";
    cin >> cantidad;

    double total = precio * cantidad;

    cout << "El total a pagar es de: Q." << total;

    return 0;
}