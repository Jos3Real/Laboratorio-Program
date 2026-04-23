#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Prototipos de funciones
void mostrarMenu();
void guardarUsuario();
void mostrarUsuarios();

int main() {

    cout << "\nNombre Estudiante: Jose Daniel Real Garcia" << endl;
    cout << "Carne Estudiante: 9941 - 25 - 837" << endl;

    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch(opcion) {
            case 1:
                guardarUsuario();
                break;
            case 2:
                mostrarUsuarios();
                break;
            case 3:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpcion invalida, intente de nuevo." << endl;
        }

    } while(opcion != 3);

    return 0;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n===== MENU =====" << endl;
    cout << "1. Guardar usuario" << endl;
    cout << "2. Mostrar usuarios" << endl;
    cout << "3. Salir" << endl;
}

// Función para guardar usuario en archivo
void guardarUsuario() {
    string nombre, posicion;
    int edad;

    ofstream archivo("usuarios.txt", ios::app); // Modo agregar

    if (archivo.fail()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    cout << "\nIngrese nombre completo: ";
    getline(cin, nombre);

    cout << "Ingrese posicion en la empresa: ";
    getline(cin, posicion);

    cout << "Ingrese edad: ";
    cin >> edad;
    cin.ignore();

    // Guardar en formato: Nombre,Posicion,Edad
    archivo << nombre << ", " << posicion << ", " << edad << endl;

    archivo.close();

    cout << "Usuario guardado correctamente." << endl;
}

// Función para mostrar usuarios desde archivo
void mostrarUsuarios() {
    ifstream archivo("usuarios.txt");
    string linea;

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo o no existe." << endl;
        return;
    }

    cout << "\n===== LISTA DE USUARIOS =====" << endl;

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}