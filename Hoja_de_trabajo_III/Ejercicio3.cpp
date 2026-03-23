#include <iostream>
using namespace std;

int main (){

    string contraseña;

    cout << "Ingrese la contraseña para ingresar: ";
    cin >> contraseña;

    while (contraseña != "1234")
    {
        cout << "Constraseña Incorrecta, intentelo nuevamente." << endl;
        cin >> contraseña;
    }

    cout << "Constraseña Correcta. Acceso permitido." << endl;

    cout << "\nEstudiante: Jose Daniel Real Garcia" << endl << "Carnet: 9941-25-837";

    return 0;
}