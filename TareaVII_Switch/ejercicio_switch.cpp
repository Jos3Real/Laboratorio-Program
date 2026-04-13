#include <iostream>

using namespace std;

int main() {
    int opcion;
    int numero;
    int contador = 0;
    int suma = 0;
    int pares = 0;
    int impares = 0;
    char continuar;

    do {

        cout << "\nEstuadiante: Jose Daniel Real Garcia" << endl << "Carne: 9941-25-837" << endl;

        // Menú principal del sistema
        cout << "\n======================================" << endl;
        cout << "SISTEMA DE GESTION INTERACTIVO" << endl;
        cout << "======================================" << endl;
        cout << "1. Registrar numeros" << endl;
        cout << "2. Mostrar estadisticas" << endl;
        cout << "3. Clasificar numeros" << endl;
        cout << "4. Salir" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n--- Opcion 1: Registrar numeros ---" << endl;
                do {
                    cout << "Ingrese un numero (entero positivo): ";
                    cin >> numero;

                    // Validación: ignorar números negativos usando 'continue'
                    if (numero < 0) {
                        cout << "Error: No se permiten numeros negativos. El valor ha sido ignorado." << endl;
                        continue; 
                    }

                    // Acumuladores y contadores
                    contador++;
                    suma += numero;

                    // Clasificación al vuelo usando el operador lógico &&
                    if (numero >= 0 && numero % 2 == 0) {
                        pares++;
                    } else if (numero >= 0 && numero % 2 != 0) {
                        impares++;
                    }

                    // Preguntar si desea continuar usando el operador lógico ||
                    cout << "Desea ingresar otro numero? (s/n): ";
                    cin >> continuar;

                } while (continuar == 's' || continuar == 'S');
                
                break; // Cierre obligatorio del caso

            case 2:
                cout << "\n--- Opcion 2: Mostrar estadisticas ---" << endl;
                if (contador == 0) {
                    cout << "No hay informacion disponible. Registre datos en la Opcion 1 primero." << endl;
                } else {
                    cout << "Total de numeros ingresados: " << contador << endl;
                    cout << "Suma total: " << suma << endl;
                    // Se utiliza static_cast para asegurar que la división tenga decimales exactos
                    cout << "Promedio: " << static_cast<double>(suma) / contador << endl;
                }
                break;

            case 3:
                cout << "\n--- Opcion 3: Clasificar numeros ---" << endl;
                // verificacion de datos combinando operadores logicos || y &&
                if (contador == 0 || (pares == 0 && impares == 0)) {
                    cout << "No hay informacion disponible. Registre datos en la Opcion 1 primero." << endl;
                } else {
                    cout << "Cantidad de numeros pares: " << pares << endl;
                    cout << "Cantidad de numeros impares: " << impares << endl;
                }
                break;

            case 4:
                cout << "\nSaliendo del sistema..." << endl;
                break;

            default:
                cout << "\nOpcion no valida. Por favor, seleccione un numero del 1 al 4." << endl;
                break;
        }

    } while (opcion != 4); 

    return 0;
}