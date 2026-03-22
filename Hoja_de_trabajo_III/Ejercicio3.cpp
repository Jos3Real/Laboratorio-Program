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

    return 0;
}