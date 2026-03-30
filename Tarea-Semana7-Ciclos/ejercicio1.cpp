#include <iostream>
#include <string>

int main() {

    using std:: cout;
    using std:: cin;
    using std:: string;

    // Nombre del estuadiante
    cout << "Nombre del estudiante: Jose Daniel Real Garcia\n\n";

    string usuario;
    int contrasena;
    int intentos_fallidos = 0;

    cout << "Ingrese usuario: ";
    cin >> usuario;
    cout << "Ingrese contrasena: ";
    cin >> contrasena;

    // Bucle while con operador logico AND (&&)
    // El ciclo continua MIENTRAS el usuario no sea "admin" O la contrasena no sea 2026
    while (!(usuario == "admin" && contrasena == 2026)) {
        cout << "Datos incorrectos.\n\n";
        intentos_fallidos++; // Contador de intentos fallidos

        cout << "Ingrese usuario: ";
        cin >> usuario;
        cout << "Ingrese contrasena: ";
        cin >> contrasena;
    }

    // Salida cuando se cumple la condicion
    cout << "Bienvenido al sistema.\n";
    cout << "Acceso concedido.\n";
    cout << "Intentos incorrectos: " << intentos_fallidos << "\n";

    return 0;
}