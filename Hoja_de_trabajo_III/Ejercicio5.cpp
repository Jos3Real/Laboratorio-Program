#include <iostream>
using namespace std;

int main () {

    int contraseña;
    int intentos = 0;

    while (intentos < 3)
    {
        cout << "\nIngrese la contraseña: ";
        cin >> contraseña;

        if (contraseña == 1234)
        {
            cout << "Bienvenido" << endl;
            break;
        }

        else {
            intentos++;
            cout << "Contrseña Incorrecta. Intentos restantes: " << (3 - intentos) << endl;
        }
        
    }
    
    if (intentos == 3)
    {
        cout << "Acceso denegado" << endl;
    }
    
    return 0;
}