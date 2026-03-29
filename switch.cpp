#include <iostream>

/*

// USO DEL SWITCH
int main () {

    using std:: cout;
    using std:: cin;

    int opcion;

    cout << "Ingrese una opcion (1-3): ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "Seleccionaste la opcion 1:";
        break;
    case 2:
        cout << "Seleccionaste la opcion 2:";
        break;
    case 3:
        cout << "Seleccionaste la opcion 3:";
        break;
    default:
        cout << "Opcion invalida";
    }

    return 0;
}*/

/*
// USO DEL CONTINUE
int main (){

    using std:: cout;
    using std:: cin;

    for (int i = 1; i <= 5; i++)
    {
        if (i == 3)
        {
            continue;
        }
        cout << i << std::endl;
    }
    return 0;
}
*/

int main() {

    using std:: cout;
    using std:: cin;

    int numero;

    for (int i = 1; i <= 5; i++)
    {
        cout << "Ingrese un numero: ";
        cin >> numero;
    
    if (numero < 0)
    {
        cout << "Numero invalida\n";
        continue;
    }

    if (numero == 0)
    {
        cout << "Fin del programa\n";
        break;
    }
    
    cout << "Numero valido: " << numero << std::endl;
    
    }

    return 0;
}