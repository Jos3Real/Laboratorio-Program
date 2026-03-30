#include <iostream>

int main() {

    using std:: cout;
    using std:: cin;

    cout << "Nombre del estudiante: Jose Daniel Real Garcia\n\n";

    int calificacion;
    int total_respuestas = 0;
    int malo = 0, regular = 0, bueno = 0, excelente = 0;

    // Bucle do-while para solicitar encuestas
    do {
        cout << "Ingrese calificacion (1 = Malo, 2 = Regular, 3 = Bueno, 4 = Excelente, 0 = Salir): ";
        cin >> calificacion;

        // Validacion de las entradas y contadores
        if (calificacion == 0) {
            // Finalizar, no se hace nada
        } else if (calificacion == 1) {
            malo++;
            total_respuestas++;
        } else if (calificacion == 2) {
            regular++;
            total_respuestas++;
        } else if (calificacion == 3) {
            bueno++;
            total_respuestas++;
        } else if (calificacion == 4) {
            excelente++;
            total_respuestas++;
        } else {
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (calificacion != 0); // Terminar si el usuario digita 0

    cout << "\nTotal de respuestas validas: " << total_respuestas << "\n";
    
    // Evitamos mostrar estadísticas en cero si no hubo encuestas
    if (total_respuestas > 0) {
        cout << "Malo: " << malo << "\n";
        cout << "Regular: " << regular << "\n";
        cout << "Bueno: " << bueno << "\n";
        cout << "Excelente: " << excelente << "\n";
    } else {
        cout << "No hubo respuestas para registrar.\n";
    }

    return 0;
}