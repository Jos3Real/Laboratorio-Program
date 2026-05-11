#include <iostream>
#include <string>

using namespace std;

// Estructura
struct Mascota {
    string nombre;
    string especie;
    string raza;
    int edad;
    float peso;
};

// funciones y procedimientos
void registrarMascota(Mascota &m);
void mostrarMascota(Mascota m);
void calcularEdadEquivalente(Mascota m);
void clasificarPeso(Mascota m);
void modificarDato(Mascota &m);

int main() {

    cout << "\nNombre: Jose Daniel Real Garcai" << endl;
    cout << "Carne: 9941-25-837" << endl;

    Mascota miMascota = {"", "", "", 0, 0.0}; // Inicialización vacía
    int opcion;
    bool registrado = false;

    do {
        cout << "\n===== REGISTRO DE MASCOTA =====" << endl;
        cout << "1. Registrar mascota" << endl;
        cout << "2. Mostrar mascota" << endl;
        cout << "3. Calcular edad equivalente" << endl;
        cout << "4. Clasificar por peso" << endl;
        cout << "5. Modificar datos" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer para usar getline después

        switch (opcion) {
            case 1:
                registrarMascota(miMascota);
                registrado = true;
                break;
            case 2:
                if (registrado) mostrarMascota(miMascota);
                else cout << "Error: Primero debe registrar una mascota.\n";
                break;
            case 3:
                if (registrado) calcularEdadEquivalente(miMascota);
                else cout << "Error: Primero debe registrar una mascota.\n";
                break;
            case 4:
                if (registrado) clasificarPeso(miMascota);
                else cout << "Error: Primero debe registrar una mascota.\n";
                break;
            case 5:
                if (registrado) modificarDato(miMascota);
                else cout << "Error: Primero debe registrar una mascota.\n";
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 6);

    return 0;
}

// Implementación de funciones

void registrarMascota(Mascota &m) {
    cout << "\n--- Ingresar Datos ---" << endl;
    cout << "Nombre: "; getline(cin, m.nombre);
    cout << "Especie: "; getline(cin, m.especie);
    cout << "Raza: "; getline(cin, m.raza);
    cout << "Edad: "; cin >> m.edad;
    cout << "Peso (kg): "; cin >> m.peso;
    cout << "¡Mascota registrada con exito!" << endl;
}

void mostrarMascota(Mascota m) {
    cout << "\n--- Informacion de la Mascota ---" << endl;
    cout << "Nombre: " << m.nombre << endl;
    cout << "Especie: " << m.especie << endl;
    cout << "Raza: " << m.raza << endl;
    cout << "Edad: " << m.edad << " años" << endl;
    cout << "Peso: " << m.peso << " kg" << endl;
}

void calcularEdadEquivalente(Mascota m) {
    int edadHumana = m.edad * 7;
    cout << "\nLa edad equivalente de " << m.nombre << " en años humanos es: " << edadHumana << " años." << endl;
}

void clasificarPeso(Mascota m) {
    cout << "\nClasificacion: ";
    if (m.peso < 5) {
        cout << "Mascota pequeña" << endl;
    } else if (m.peso >= 5 && m.peso <= 20) {
        cout << "Mascota mediana" << endl;
    } else {
        cout << "Mascota grande" << endl;
    }
}

void modificarDato(Mascota &m) {
    int modOpcion;
    cout << "\n¿Que dato desea modificar?" << endl;
    cout << "1. Nombre\n2. Edad\n3. Peso\nSeleccion: ";
    cin >> modOpcion;
    cin.ignore();

    switch (modOpcion) {
        case 1:
            cout << "Nuevo nombre: "; getline(cin, m.nombre);
            break;
        case 2:
            cout << "Nueva edad: "; cin >> m.edad;
            break;
        case 3:
            cout << "Nuevo peso: "; cin >> m.peso;
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}