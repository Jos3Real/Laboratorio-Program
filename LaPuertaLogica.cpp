#include <iostream>
#include <iomanip>
#include <windows.h> 

using namespace std;

int main () {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string nom_usuario;
    cout << "Nombre del Usuario: ";
    getline (cin, nom_usuario);

    int edad;
    cout << "Edad del Usuario: ";
    cin >> edad;

    float prom_academico;
    cout << "¿Cual es el Promedio Académico del Usuario? "
    cin >> prom_academico

    int club;
    cout << "¿El Usuario pertenece al club de programación?, si la respuesta es SI colocar 1 y si la respuesta es NO colocar 0"
    cin >> club;

    if ((edad >= 18 && prom_academico >= 85)||
        (club == 1 && prom_academico >= 75)||
        (prom_academico >= 95))
    {
        cout << "Bienvenido " nom_usuario << "." << endl;
        cout << "Acceso Autorizado";
    }

    if (nom_usuario == "David Alvarez")
    {
        cout << "Acceso Especial Concedido"
    }

    
    
    

    return 0;
}