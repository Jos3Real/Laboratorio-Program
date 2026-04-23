#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Prototipos: 3 Funciones y Procedimientos

double calcularSubtotal(int cantidad, double precio);
double calcularDescuento(double subtotal, int tipoPago);
double calcularTotal(double subtotal, double descuento);

void mostrarMenu();
void registrarVenta();
void mostrarTodasLasVentas();
void generarReporteGeneral();
void buscarVentasPorMonto();
void dibujarSeparador(); // Procedimiento extra para cumplir con el for

// Funcion Principal

int main() {

    cout << "\nNombre Estudiante: Jose Daniel Real Garcia" << endl;
    cout << "Carne Estudiante: 9941 - 25 - 837" << endl;

    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        // Validar que el usuario ingrese un número y no una letra
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nError: Entrada invalida. Ingrese un numero.\n";
            continue; // Obligatorio: Uso de continue para reiniciar el ciclo
        }

        switch (opcion) {
            case 1: registrarVenta(); break;
            case 2: mostrarTodasLasVentas(); break;
            case 3: generarReporteGeneral(); break;
            case 4: buscarVentasPorMonto(); break;
            case 5: cout << "\nSaliendo del sistema de ventas...\n"; break;
            default: cout << "\nOpcion no valida. Intente de nuevo.\n"; break;
        }
    } while (opcion != 5);

    return 0;
}

// Implementacion de procedimientos (void)

void dibujarSeparador() {
    // Obligatorio: Uso de un for en un punto lógico
    for (int i = 0; i < 50; i++) {
        cout << "-";
    }
    cout << endl;
}

void mostrarMenu() {
    cout << "\n";
    dibujarSeparador();
    cout << "            SISTEMA DE CONTROL DE VENTAS\n";
    dibujarSeparador();
    cout << "1. Registrar una venta\n";
    cout << "2. Mostrar todas las ventas\n";
    cout << "3. Generar reporte general\n";
    cout << "4. Buscar ventas por monto\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

void registrarVenta() {
    string cliente, producto, tipoPagoStr;
    int cantidad, tipoPago;
    double precio, subtotal, descuento, total;

    cin.ignore(); // Limpiar el buffer de entrada antes de usar getline
    cout << "\n--- REGISTRO DE VENTA ---\n";
    
    cout << "Nombre del cliente (o escriba 'cancelar' para abortar): ";
    getline(cin, cliente);

    // Obligatorio: Uso de break para salir tempranamente si el usuario cancela
    if (cliente == "cancelar") {
        cout << "Registro cancelado por el usuario.\n";
        return; 
    }

    cout << "Nombre del producto: ";
    getline(cin, producto);

    // Validación de cantidad con while
    cantidad = 0;
    while (cantidad <= 0) {
        cout << "Cantidad (mayor a 0): ";
        cin >> cantidad;
        if (cantidad <= 0) cout << "Error: La cantidad debe ser mayor a 0.\n";
    }

    // Validación de precio con while
    precio = 0;
    while (precio <= 0) {
        cout << "Precio unitario: Q.";
        cin >> precio;
        if (precio <= 0) cout << "Error: El precio debe ser mayor a 0.\n";
    }

    // Validación de tipo de pago con do-while
    do {
        cout << "Tipo de pago (1 = Efectivo, 2 = Tarjeta, 3 = Transferencia): ";
        cin >> tipoPago;
        if (tipoPago < 1 || tipoPago > 3) cout << "Error: Ingrese 1, 2 o 3.\n";
    } while (tipoPago < 1 || tipoPago > 3);

    // Asignar texto según el tipo de pago
    if (tipoPago == 1) tipoPagoStr = "Efectivo";
    else if (tipoPago == 2) tipoPagoStr = "Tarjeta";
    else tipoPagoStr = "Transferencia";

    // Calculos llamando a las funciones
    subtotal = calcularSubtotal(cantidad, precio);
    descuento = calcularDescuento(subtotal, tipoPago);
    total = calcularTotal(subtotal, descuento);

    // Almacenamiento en archivo fstream
    ofstream archivo("ventas.txt", ios::app); // ios::app para no sobreescribir
    if (archivo.is_open()) {
        archivo << cliente << ", " << producto << ", " << cantidad << ", " 
                << precio << ", " << subtotal << ", " << descuento << ", " 
                << total << ", " << tipoPagoStr << "\n";
        archivo.close();
        cout << "\nVenta registrada correctamente.\n";
    } else {
        cout << "\nError al abrir el archivo ventas.txt\n";
    }
}

void mostrarTodasLasVentas() {
    ifstream archivo("ventas.txt");
    string linea;

    cout << "\n";
    dibujarSeparador();
    cout << "           TODAS LAS VENTAS\n";
    dibujarSeparador();

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo o no hay ventas registradas.\n";
    }
}

void generarReporteGeneral() {
    ifstream archivo("ventas.txt");
    if (!archivo.is_open()) {
        cout << "\nNo hay datos para generar el reporte.\n";
        return;
    }

    int totalVentas = 0, efectivo = 0, tarjeta = 0, transferencia = 0, conDescuento = 0;
    double sumaTotal = 0.0;

    string cliente, producto, tipoPago;
    int cantidad;
    double precio, subtotal, descuento, total;
    char coma; // Para consumir las comas del archivo

    // Lectura estructurada separada por comas
    while (getline(archivo, cliente, ',') && getline(archivo, producto, ',')) {
        // Extraemos todos los números y la última palabra (tipoPago) de una sola vez
        archivo >> cantidad >> coma >> precio >> coma >> subtotal >> coma 
                >> descuento >> coma >> total >> coma >> tipoPago;
        
        // Limpiamos el resto de la línea para eliminar el \r\n invisible
        archivo.ignore(1000, '\n');

        // Procesamiento de métricas
        totalVentas++;
        sumaTotal += total;

        if (tipoPago == "Efectivo") efectivo++;
        else if (tipoPago == "Tarjeta") tarjeta++;
        else if (tipoPago == "Transferencia") transferencia++;

        if (descuento > 0) conDescuento++;
    }
    archivo.close();

    cout << "\n";
    dibujarSeparador();
    cout << "-----------REPORTE GENERAL\n";
    dibujarSeparador();
    cout << "1. Total de ventas registradas: " << totalVentas << endl;
    cout << "2. Suma total vendida: Q." << sumaTotal << endl;
    if (totalVentas > 0) {
        cout << "3. Promedio de venta: Q." << (sumaTotal / totalVentas) << endl;
    }
    cout << "4. Ventas en Efectivo: " << efectivo << endl;
    cout << "5. Ventas en Tarjeta: " << tarjeta << endl;
    cout << "6. Ventas en Transferencia: " << transferencia << endl;
    cout << "7. Ventas con descuento aplicado: " << conDescuento << endl;
}

void buscarVentasPorMonto() {
    double montoBuscado;
    cout << "\nMostrar ventas mayores o iguales a Q: ";
    cin >> montoBuscado;

    ifstream archivo("ventas.txt");
    if (!archivo.is_open()) {
        cout << "\nNo hay datos guardados.\n";
        return;
    }

    string cliente, producto, tipoPago;
    int cantidad;
    double precio, subtotal, descuento, total;
    char coma;
    bool encontrada = false;

    cout << "\nResultados de la busqueda:\n";
    dibujarSeparador();

    while (getline(archivo, cliente, ',') && getline(archivo, producto, ',')) {
        archivo >> cantidad >> coma >> precio >> coma >> subtotal >> coma 
                >> descuento >> coma >> total >> coma >> tipoPago;
        
        // Limpiamos el buffer
        archivo.ignore(1000, '\n');

        if (total >= montoBuscado) {
            cout << "Cliente: " << cliente << " | Producto: " << producto 
                 << " | Total: Q." << total << " | Pago: " << tipoPago << endl;
            encontrada = true;
        }
    }
    archivo.close();

    if (!encontrada) {
        cout << "No se encontraron ventas mayores o iguales a Q" << montoBuscado << endl;
    }
}

// Implementacion de Funciones

double calcularSubtotal(int cantidad, double precio) {
    return cantidad * precio;
}

double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0.0;
    // 5% si el subtotal >= Q500
    if (subtotal >= 500) {
        descuento += subtotal * 0.05; 
    }
    // 2% adicional si es efectivo y subtotal >= Q300
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02; 
    }
    return descuento;
}

double calcularTotal(double subtotal, double descuento) {
    return subtotal - descuento;
}