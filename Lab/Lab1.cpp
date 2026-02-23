#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    string usuario;
    cout << "Ingrese su nombre: ";
    getline(cin, usuario);

    double precio_producto;
    cout << "Ingrese el precio del producto: ";
    cin >> precio_producto;

    double cantidad;
    cout << "Ingrese la cantidad comprada: ";
    cin >> cantidad;

    double subtotal = precio_producto * cantidad;
    double iva = subtotal * 0.12;
    double total = subtotal + iva;

    cout << "Usuario: " << usuario << endl;
    cout << "Precio del Producto: Q." << precio_producto << endl;
    cout << "Cantidad Comprada: " << cantidad << endl; 
    cout << fixed << setprecision(2);
    cout << "El total a pagar es de: Q." << total;

    return 0;
}

