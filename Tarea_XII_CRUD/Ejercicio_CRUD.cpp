#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// --- Struct Obligatorio ---
struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

const char* ARCHIVO = "productos.dat";
const float IVA_PORCENTAJE = 0.12; // 12% de IVA

// --- Funciones ---
void menuPrincipal();
void menuProductos();
void registrarProducto();
void listarProductos();
void buscarPorCodigo();
void buscarPorNombre();
void modificarPrecio();
void actualizarStock();
void eliminarProducto();
void procesoVenta();

// Funciones auxiliares
bool existeArchivo();
void crearArchivoSiNoExiste();

int main() {
    cout << "========================================\n";
    cout << " ESTUDIANTE: Jose Daniel Real Garcia \n";
    cout << " CARNE: 9941 - 25 - 837 \n";
    cout << "========================================\n";
    
    crearArchivoSiNoExiste();
    menuPrincipal();
    return 0;
}

// --- Menus ---
void menuPrincipal() {
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Gestion de productos\n";
        cout << "2. Proceso de venta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuProductos(); break;
            case 2: procesoVenta(); break;
            case 3: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

void menuProductos() {
    int opcion;
    do {
        cout << "\n--- GESTION DE PRODUCTOS ---\n";
        cout << "1. Registrar producto\n";
        cout << "2. Listar productos activos\n";
        cout << "3. Buscar producto por codigo\n";
        cout << "4. Buscar producto por nombre\n";
        cout << "5. Modificar precio\n";
        cout << "6. Actualizar stock\n";
        cout << "7. Eliminar / desactivar producto\n";
        cout << "8. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarPorCodigo(); break;
            case 4: buscarPorNombre(); break;
            case 5: modificarPrecio(); break;
            case 6: actualizarStock(); break;
            case 7: eliminarProducto(); break;
            case 8: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 8);
}

// --- Gestión de productos (CRUD) ---

void registrarProducto() {
    Producto p;
    cout << "\n-- Registrar Producto --\n";
    cout << "Codigo: ";
    cin >> p.codigo;
    cin.ignore(); // Limpiar el buffer
    cout << "Nombre: ";
    cin.getline(p.nombre, 50);
    cout << "Precio: ";
    cin >> p.precio;
    cout << "Stock inicial: ";
    cin >> p.stock;
    p.activo = true;

    // Abrir en modo de añadir al final en binario
    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    if (archivo.is_open()) {
        archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
        archivo.close();
        cout << "Producto registrado con exito.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

void listarProductos() {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);
    
    cout << "\n-- Listado de Productos Activos --\n";
    cout << left << setw(10) << "Codigo" 
         << setw(20) << "Nombre" 
         << setw(10) << "Precio" 
         << "Stock\n";
    cout << "--------------------------------------------------\n";
    
    bool hayProductos = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.activo) {
            cout << left << setw(10) << p.codigo 
                 << setw(20) << p.nombre 
                 << setw(10) << p.precio 
                 << p.stock << "\n";
            hayProductos = true;
        }
    }
    archivo.close();
    if (!hayProductos) cout << "No hay productos activos registrados.\n";
}

void buscarPorCodigo() {
    int codigoBuscado;
    cout << "\nIngrese el codigo del producto a buscar: ";
    cin >> codigoBuscado;

    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            cout << "\nProducto Encontrado:\n";
            cout << "Nombre: " << p.nombre << "\nPrecio: Q" << p.precio << "\nStock: " << p.stock << "\n";
            encontrado = true;
            break;
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado o inactivo.\n";
}

void buscarPorNombre() {
    char nombreBuscado[50];
    cout << "\nIngrese el nombre del producto a buscar: ";
    cin.ignore();
    cin.getline(nombreBuscado, 50);

    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        // strcasecmp o similar no es estandar, hacemos comparacion exacta (sensible a mayusculas)
        // Para simplificar segun requerimientos basicos usamos strcmp
        if (strcmp(p.nombre, nombreBuscado) == 0 && p.activo) {
            cout << "\nProducto Encontrado:\n";
            cout << "Codigo: " << p.codigo << "\nPrecio: Q" << p.precio << "\nStock: " << p.stock << "\n";
            encontrado = true;
            break; // O quitamos break si puede haber nombres duplicados
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado o inactivo.\n";
}

void modificarPrecio() {
    int codigo;
    cout << "\nIngrese el codigo del producto para modificar precio: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::in | ios::out | ios::binary);
    Producto p;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "Precio actual: Q" << p.precio << "\n";
            cout << "Nuevo precio: ";
            cin >> p.precio;

            // Retroceder un registro para sobrescribir
            archivo.seekp(archivo.tellg() - static_cast<streampos>(sizeof(Producto)));
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
            encontrado = true;
            cout << "Precio actualizado.\n";
            break;
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado.\n";
}

void actualizarStock() {
    int codigo;
    cout << "\nIngrese el codigo del producto para actualizar stock: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::in | ios::out | ios::binary);
    Producto p;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "Stock actual: " << p.stock << "\n";
            cout << "Nuevo stock: ";
            cin >> p.stock;

            archivo.seekp(archivo.tellg() - static_cast<streampos>(sizeof(Producto)));
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
            encontrado = true;
            cout << "Stock actualizado.\n";
            break;
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado.\n";
}

void eliminarProducto() {
    int codigo;
    cout << "\nIngrese el codigo del producto a desactivar: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::in | ios::out | ios::binary);
    Producto p;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            p.activo = false; // Desactivacion logica
            archivo.seekp(archivo.tellg() - static_cast<streampos>(sizeof(Producto)));
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
            encontrado = true;
            cout << "Producto desactivado correctamente.\n";
            break;
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado o ya inactivo.\n";
}

// --- Proceso de Venta ---
void procesoVenta() {
    int codigo, cantidad;
    cout << "\n--- PROCESO DE VENTA ---\n";
    cout << "Ingrese el codigo del producto: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::in | ios::out | ios::binary);
    Producto p;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            encontrado = true;
            cout << "Producto: " << p.nombre << "\n";
            cout << "Precio unitario: Q" << p.precio << "\n";
            cout << "Stock disponible: " << p.stock << "\n";

            cout << "Ingrese la cantidad a comprar: ";
            cin >> cantidad;

            if (cantidad > p.stock) {
                cout << "Error: Stock insuficiente.\n";
            } else if (cantidad <= 0) {
                cout << "Error: Cantidad invalida.\n";
            } else {
                // Calcular factura
                float subtotal = cantidad * p.precio;
                float iva = subtotal * IVA_PORCENTAJE;
                float total = subtotal + iva;

                cout << "\n--- TICKET DE VENTA ---\n";
                cout << "Cantidad: " << cantidad << "\n";
                cout << "Subtotal: Q" << fixed << setprecision(2) << subtotal << "\n";
                cout << "IVA (12%): Q" << iva << "\n";
                cout << "TOTAL A PAGAR: Q" << total << "\n";
                cout << "-----------------------\n";

                // Descontar stock
                p.stock -= cantidad;
                archivo.seekp(archivo.tellg() - static_cast<streampos>(sizeof(Producto)));
                archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
                cout << "Venta procesada y stock actualizado.\n";
            }
            break;
        }
    }
    archivo.close();
    if (!encontrado) cout << "Producto no encontrado o inactivo.\n";
}

// --- Funciones de utilidad ---
void crearArchivoSiNoExiste() {
    ifstream archivoVerificador(ARCHIVO);
    if (!archivoVerificador.is_open()) {
        ofstream archivoNuevo(ARCHIVO, ios::binary);
        archivoNuevo.close();
    } else {
        archivoVerificador.close();
    }
}