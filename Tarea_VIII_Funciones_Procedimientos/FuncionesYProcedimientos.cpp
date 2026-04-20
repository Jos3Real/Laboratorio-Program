#include <iostream>
#include <string>

using namespace std;

// Funciones 
double calcularPromedio(double sumaNotas, int cantidad);
string determinarEstado(double promedio);
string determinarCategoria(double promedio);
void mostrarResultado(string nombre, string curso, double promedio, string estado, string categoria);

int main() {

    cout << "\nNombre: Jose Daniel Real Garcia" << endl;
    cout << "Carne: 9941 - 25 - 837";

    string nombreEstudiante, nombreCurso;
    int cantidadNotas;
    double notaActual;
    double sumaTotal = 0;

    // Ingreso de datos
    cout << "\nIngrese el nombre del estudiante: ";
    getline(cin, nombreEstudiante);
    cout << "Ingrese el curso: ";
    getline(cin, nombreCurso);
    cout << "Ingrese la cantidad de notas: ";
    cin >> cantidadNotas;

    // Ciclo para solicitar las notas una por una
    for (int i = 1; i <= cantidadNotas; i++) {
        cout << "Ingrese la nota " << i << ": ";
        cin >> notaActual;
        sumaTotal += notaActual; // sumatoria de cada nota al total
    }

    // Procesamiento de datos mediante las funciones
    double promedioFinal = calcularPromedio(sumaTotal, cantidadNotas);
    string estadoEstudiante = determinarEstado(promedioFinal);
    string categoriaEstudiante = determinarCategoria(promedioFinal);

    // Salida de resultados mediante un procedimiento
    mostrarResultado(nombreEstudiante, nombreCurso, promedioFinal, estadoEstudiante, categoriaEstudiante);

    return 0;
}

// Función para calcular el promedio
double calcularPromedio(double sumaNotas, int cantidad) {
    if (cantidad <= 0) return 0;
    return sumaNotas / cantidad;
}

// Función para determinar el estado si es Aprobado o Reprobado
string determinarEstado(double promedio) {
    if (promedio >= 61) {
        return "Aprobado";
    } else {
        return "Reprobado";
    }
}

// Categoría según el promedio
string determinarCategoria(double promedio) {
    if (promedio >= 85 && promedio <= 100) {
        return "Excelente";
    } else if (promedio >= 70) {
        return "Bueno";
    } else if (promedio >= 61) {
        return "Regular";
    } else {
        return "Deficiente";
    }
}

// Procedimiento para mostrar el resultado final
void mostrarResultado(string nombre, string curso, double promedio, string estado, string categoria) {
    cout << "\n----- RESULTADO FINAL -----" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Curso: " << curso << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Estado: " << estado << endl;
    cout << "Categoria: " << categoria << endl;
    cout << "---------------------------" << endl;
}