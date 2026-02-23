#include <iostream>
#include <windows.h> 

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    double precio_inicial;
    cout << "Ingrese el Precio Inicial del Producto en Q: ";
    cin >> precio_inicial;
    
    double porcentaje_incremento;
    cout << "Ingrese el Porcentaje de Incremento para el Precio Inicial del Producto: ";
    cin >> porcentaje_incremento;

    double precio_nuevo = precio_inicial + (precio_inicial * porcentaje_incremento / 100);

    cout << "El Calculo del nuevo precio del producto es de: Q." << precio_nuevo;

    return 0;
}