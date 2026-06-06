// ============================================================
//   SISTEMA DE GESTIÓN DE VENTAS E INVENTARIO PARA TIENDA
//   Proyecto Final de Programación — C++
//   Autor: José Daniel Real
//   Fecha: 2026
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cstring>
#include <stdexcept>

using namespace std;

// ============================================================
//   CONSTANTES GLOBALES
// ============================================================
const string ARCHIVO_PRODUCTOS = "productos.dat";
const string ARCHIVO_VENTAS    = "ventas.dat";
const string ARCHIVO_REPORTE   = "reporte.txt";
const int    MAX_PRODUCTOS      = 200;
const int    MAX_DETALLES       = 20;
const int    MAX_VENTAS         = 500;
const double IVA                = 0.12;
const string AUTOR              = "SISTEMA DE GESTION DE TIENDA";
const string VERSION            = "v1.0";

// ============================================================
//   ESTRUCTURAS
// ============================================================

struct Producto {
    int    codigo;
    char   nombre[60];
    char   categoria[30];
    double precio;
    int    stock;
    int    totalVendido;
    bool   activo;
};

struct DetalleVenta {
    int    codigoProducto;
    char   nombreProducto[60];
    int    cantidad;
    double precioUnitario;
    double subtotalDetalle;
};

struct Venta {
    int          idVenta;
    int          dia;
    int          mes;
    int          anio;
    int          hora;
    int          minuto;
    DetalleVenta detalles[MAX_DETALLES];
    int          numDetalles;
    double       subtotal;
    double       descuento;
    double       iva;
    double       total;
    int          totalArticulos;
};

// ============================================================
//   VARIABLES GLOBALES
// ============================================================
Producto productos[MAX_PRODUCTOS];
int      numProductos = 0;
Venta    ventas[MAX_VENTAS];
int      numVentas = 0;

// Matriz ventas por mes [mes 1-12][hasta 31 dias]
double ventasPorMes[12][31];

// ============================================================
//   PROTOTIPOS DE FUNCIONES
// ============================================================

// --- Utilidades de interfaz ---
void limpiarPantalla();
void pausar();
void mostrarEncabezado(const string& titulo);
void mostrarLineaSeparadora();
int  leerEnteroSeguro(const string& mensaje, int minVal, int maxVal);
double leerDoubleSeguro(const string& mensaje, double minVal);
string leerStringSeguro(const string& mensaje, int maxLen);

// --- Módulo 1: Gestión de Productos ---
void menuProductos();
void registrarProducto();
void listarProductos();
void buscarProductoPorCodigo();
void buscarProductoPorNombre();
void actualizarStock();
void modificarPrecio();
void eliminarProducto();
int  encontrarProductoPorCodigo(int codigo);

// --- Módulo 2: Proceso de Venta ---
void menuVentas();
void crearVenta();
double calcularDescuento(double subtotal, int totalArticulos);
void mostrarResumenVenta(const Venta& v);

// --- Módulo 3: Reportes ---
void menuReportes();
void reporteStockBajo();
void reporteProductosMasVendidos();
void reporteVentasDia();
void reporteVentasPorMes();
void ordenarProductosPorPrecio(bool ascendente);
void ordenarProductosPorStock(bool ascendente);
void ordenarProductosPorVentas();

// --- Módulo 4: Utilidades del Sistema ---
void menuUtilidades();
void exportarReporteTxt();
void reiniciarInventario();
void mostrarEstadisticasGenerales();

// --- Manejo de Archivos ---
void cargarProductos();
void guardarProductos();
void cargarVentas();
void guardarVenta(const Venta& v);
void cargarMatrizVentas();

// --- Menú Principal ---
void menuPrincipal();
void mostrarBienvenida();

// ============================================================
//   IMPLEMENTACIÓN: UTILIDADES DE INTERFAZ
// ============================================================

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarLineaSeparadora() {
    cout << "  " << string(60, '=') << "\n";
}

void mostrarEncabezado(const string& titulo) {
    limpiarPantalla();
    mostrarLineaSeparadora();
    cout << "  " << AUTOR << " " << VERSION << "\n";
    mostrarLineaSeparadora();
    cout << "  >> " << titulo << "\n";
    mostrarLineaSeparadora();
    cout << "\n";
}

int leerEnteroSeguro(const string& mensaje, int minVal, int maxVal) {
    int valor = 0;
    while (true) {
        try {
            cout << "  " << mensaje;
            string entrada;
            getline(cin, entrada);
            if (entrada.empty()) throw invalid_argument("Entrada vacía.");
            size_t pos;
            valor = stoi(entrada, &pos);
            if (pos != entrada.size()) throw invalid_argument("Caracteres no numéricos.");
            if (valor < minVal || valor > maxVal) {
                throw out_of_range("Valor fuera de rango [" + to_string(minVal) +
                                   " - " + to_string(maxVal) + "].");
            }
            break;
        } catch (const invalid_argument& e) {
            cout << "  [ERROR] Entrada inválida: " << e.what() << " Intente de nuevo.\n";
        } catch (const out_of_range& e) {
            cout << "  [ERROR] " << e.what() << " Intente de nuevo.\n";
        }
    }
    return valor;
}

double leerDoubleSeguro(const string& mensaje, double minVal) {
    double valor = 0.0;
    while (true) {
        try {
            cout << "  " << mensaje;
            string entrada;
            getline(cin, entrada);
            if (entrada.empty()) throw invalid_argument("Entrada vacía.");
            size_t pos;
            valor = stod(entrada, &pos);
            if (pos != entrada.size()) throw invalid_argument("Formato numérico inválido.");
            if (valor < minVal) {
                throw out_of_range("El valor debe ser >= " + to_string(minVal));
            }
            break;
        } catch (const invalid_argument& e) {
            cout << "  [ERROR] " << e.what() << " Intente de nuevo.\n";
        } catch (const out_of_range& e) {
            cout << "  [ERROR] " << e.what() << " Intente de nuevo.\n";
        }
    }
    return valor;
}

string leerStringSeguro(const string& mensaje, int maxLen) {
    string valor;
    while (true) {
        try {
            cout << "  " << mensaje;
            getline(cin, valor);
            if (valor.empty()) throw invalid_argument("El texto no puede estar vacío.");
            if ((int)valor.size() > maxLen) {
                throw length_error("Máximo " + to_string(maxLen) + " caracteres.");
            }
            break;
        } catch (const invalid_argument& e) {
            cout << "  [ERROR] " << e.what() << " Intente de nuevo.\n";
        } catch (const length_error& e) {
            cout << "  [ERROR] " << e.what() << " Intente de nuevo.\n";
        }
    }
    return valor;
}

// ============================================================
//   IMPLEMENTACIÓN: MANEJO DE ARCHIVOS
// ============================================================

void cargarProductos() {
    try {
        ifstream archivo(ARCHIVO_PRODUCTOS, ios::binary);
        if (!archivo.is_open()) {
            numProductos = 0;
            return;
        }
        archivo.read(reinterpret_cast<char*>(&numProductos), sizeof(int));
        if (numProductos < 0 || numProductos > MAX_PRODUCTOS)
            throw runtime_error("Archivo de productos corrupto.");
        archivo.read(reinterpret_cast<char*>(productos),
                     sizeof(Producto) * numProductos);
        archivo.close();
    } catch (const exception& e) {
        cerr << "  [ADVERTENCIA] No se pudo cargar productos: " << e.what() << "\n";
        numProductos = 0;
    }
}

void guardarProductos() {
    try {
        ofstream archivo(ARCHIVO_PRODUCTOS, ios::binary | ios::trunc);
        if (!archivo.is_open())
            throw runtime_error("No se pudo abrir " + ARCHIVO_PRODUCTOS + " para escritura.");
        archivo.write(reinterpret_cast<char*>(&numProductos), sizeof(int));
        archivo.write(reinterpret_cast<char*>(productos),
                      sizeof(Producto) * numProductos);
        archivo.close();
    } catch (const exception& e) {
        cerr << "  [ERROR] " << e.what() << "\n";
    }
}

void cargarVentas() {
    try {
        ifstream archivo(ARCHIVO_VENTAS, ios::binary);
        if (!archivo.is_open()) {
            numVentas = 0;
            return;
        }
        archivo.read(reinterpret_cast<char*>(&numVentas), sizeof(int));
        if (numVentas < 0 || numVentas > MAX_VENTAS)
            throw runtime_error("Archivo de ventas corrupto.");
        archivo.read(reinterpret_cast<char*>(ventas),
                     sizeof(Venta) * numVentas);
        archivo.close();
    } catch (const exception& e) {
        cerr << "  [ADVERTENCIA] No se pudo cargar ventas: " << e.what() << "\n";
        numVentas = 0;
    }
}

void guardarVenta(const Venta& v) {
    try {
        // Añadir venta al arreglo en memoria
        if (numVentas < MAX_VENTAS) {
            ventas[numVentas++] = v;
        }
        // Reescribir archivo completo
        ofstream archivo(ARCHIVO_VENTAS, ios::binary | ios::trunc);
        if (!archivo.is_open())
            throw runtime_error("No se pudo abrir " + ARCHIVO_VENTAS + " para escritura.");
        archivo.write(reinterpret_cast<char*>(&numVentas), sizeof(int));
        archivo.write(reinterpret_cast<char*>(ventas),
                      sizeof(Venta) * numVentas);
        archivo.close();
    } catch (const exception& e) {
        cerr << "  [ERROR] Al guardar venta: " << e.what() << "\n";
    }
}

void cargarMatrizVentas() {
    // Inicializar matriz a cero
    for (int m = 0; m < 12; m++)
        for (int d = 0; d < 31; d++)
            ventasPorMes[m][d] = 0.0;

    // Recorrer ventas y acumular
    for (int i = 0; i < numVentas; i++) {
        int m = ventas[i].mes - 1;   // 0-indexed
        int d = ventas[i].dia - 1;   // 0-indexed
        if (m >= 0 && m < 12 && d >= 0 && d < 31) {
            ventasPorMes[m][d] += ventas[i].total;
        }
    }
}

// ============================================================
//   IMPLEMENTACIÓN: MÓDULO 1 — GESTIÓN DE PRODUCTOS
// ============================================================

int encontrarProductoPorCodigo(int codigo) {
    // Búsqueda secuencial por código
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].codigo == codigo && productos[i].activo)
            return i;
    }
    return -1;
}

void registrarProducto() {
    mostrarEncabezado("REGISTRAR NUEVO PRODUCTO");

    if (numProductos >= MAX_PRODUCTOS) {
        cout << "  [ERROR] Capacidad máxima de productos alcanzada.\n";
        pausar();
        return;
    }

    Producto p;
    p.totalVendido = 0;
    p.activo       = true;

    // Código único
    while (true) {
        p.codigo = leerEnteroSeguro("Código del producto (1-9999): ", 1, 9999);
        if (encontrarProductoPorCodigo(p.codigo) == -1) break;
        cout << "  [ERROR] Ese código ya existe. Use otro.\n";
    }

    string nombre = leerStringSeguro("Nombre del producto (max 59 chars): ", 59);
    strncpy(p.nombre, nombre.c_str(), 59);
    p.nombre[59] = '\0';

    string cat = leerStringSeguro("Categoría (max 29 chars): ", 29);
    strncpy(p.categoria, cat.c_str(), 29);
    p.categoria[29] = '\0';

    p.precio = leerDoubleSeguro("Precio unitario (Q): ", 0.01);
    p.stock  = leerEnteroSeguro("Stock inicial: ", 0, 99999);

    productos[numProductos++] = p;
    guardarProductos();

    cout << "\n  [OK] Producto registrado exitosamente.\n";
    cout << "  Código: " << p.codigo << " | Nombre: " << p.nombre << "\n";
    pausar();
}

void listarProductos() {
    mostrarEncabezado("LISTADO DE PRODUCTOS ACTIVOS");

    bool hayProductos = false;
    cout << "  " << left
         << setw(6)  << "COD"
         << setw(25) << "NOMBRE"
         << setw(15) << "CATEGORÍA"
         << setw(10) << "PRECIO"
         << setw(8)  << "STOCK"
         << setw(8)  << "VENDIDO"
         << "\n";
    mostrarLineaSeparadora();

    for (int i = 0; i < numProductos; i++) {
        if (!productos[i].activo) continue;
        hayProductos = true;
        cout << "  " << left
             << setw(6)  << productos[i].codigo
             << setw(25) << productos[i].nombre
             << setw(15) << productos[i].categoria
             << "Q" << setw(9) << fixed << setprecision(2) << productos[i].precio
             << setw(8)  << productos[i].stock
             << setw(8)  << productos[i].totalVendido
             << "\n";
    }

    if (!hayProductos)
        cout << "  No hay productos registrados.\n";

    pausar();
}

void buscarProductoPorCodigo() {
    mostrarEncabezado("BUSCAR PRODUCTO POR CÓDIGO");

    int codigo = leerEnteroSeguro("Ingrese el código a buscar: ", 1, 9999);
    int idx    = encontrarProductoPorCodigo(codigo);

    if (idx == -1) {
        cout << "\n  [INFO] No se encontró producto con código " << codigo << ".\n";
    } else {
        Producto& p = productos[idx];
        cout << "\n  === PRODUCTO ENCONTRADO ===\n";
        cout << "  Código   : " << p.codigo     << "\n";
        cout << "  Nombre   : " << p.nombre     << "\n";
        cout << "  Categoría: " << p.categoria  << "\n";
        cout << "  Precio   : Q" << fixed << setprecision(2) << p.precio << "\n";
        cout << "  Stock    : " << p.stock       << " unidades\n";
        cout << "  Vendido  : " << p.totalVendido << " unidades\n";
    }
    pausar();
}

void buscarProductoPorNombre() {
    mostrarEncabezado("BUSCAR PRODUCTO POR NOMBRE");

    string busqueda = leerStringSeguro("Ingrese parte del nombre a buscar: ", 59);

    // Convertir búsqueda a minúsculas para comparación insensible
    string busqLow = busqueda;
    transform(busqLow.begin(), busqLow.end(), busqLow.begin(), ::tolower);

    bool encontrado = false;
    cout << "\n  Resultados:\n";
    mostrarLineaSeparadora();

    // Búsqueda secuencial por nombre
    for (int i = 0; i < numProductos; i++) {
        if (!productos[i].activo) continue;
        string nombreLow = string(productos[i].nombre);
        transform(nombreLow.begin(), nombreLow.end(), nombreLow.begin(), ::tolower);

        if (nombreLow.find(busqLow) != string::npos) {
            encontrado = true;
            cout << "  Cód: " << productos[i].codigo
                 << " | " << productos[i].nombre
                 << " | Q" << fixed << setprecision(2) << productos[i].precio
                 << " | Stock: " << productos[i].stock << "\n";
        }
    }

    if (!encontrado)
        cout << "  No se encontraron coincidencias para: \"" << busqueda << "\"\n";

    pausar();
}

void actualizarStock() {
    mostrarEncabezado("ACTUALIZAR STOCK DE PRODUCTO");

    int codigo = leerEnteroSeguro("Código del producto: ", 1, 9999);
    int idx    = encontrarProductoPorCodigo(codigo);

    if (idx == -1) {
        cout << "  [ERROR] Producto no encontrado.\n";
        pausar();
        return;
    }

    cout << "  Producto: " << productos[idx].nombre
         << " | Stock actual: " << productos[idx].stock << "\n";

    int nuevoStock = leerEnteroSeguro("Nuevo stock: ", 0, 99999);
    productos[idx].stock = nuevoStock;
    guardarProductos();

    cout << "  [OK] Stock actualizado a " << nuevoStock << " unidades.\n";
    pausar();
}

void modificarPrecio() {
    mostrarEncabezado("MODIFICAR PRECIO DE PRODUCTO");

    int codigo = leerEnteroSeguro("Código del producto: ", 1, 9999);
    int idx    = encontrarProductoPorCodigo(codigo);

    if (idx == -1) {
        cout << "  [ERROR] Producto no encontrado.\n";
        pausar();
        return;
    }

    cout << "  Producto: " << productos[idx].nombre
         << " | Precio actual: Q" << fixed << setprecision(2) << productos[idx].precio << "\n";

    double nuevoPrecio = leerDoubleSeguro("Nuevo precio (Q): ", 0.01);
    productos[idx].precio = nuevoPrecio;
    guardarProductos();

    cout << "  [OK] Precio actualizado a Q" << fixed << setprecision(2) << nuevoPrecio << ".\n";
    pausar();
}

void eliminarProducto() {
    mostrarEncabezado("ELIMINAR / DESACTIVAR PRODUCTO");

    int codigo = leerEnteroSeguro("Código del producto a eliminar: ", 1, 9999);
    int idx    = encontrarProductoPorCodigo(codigo);

    if (idx == -1) {
        cout << "  [ERROR] Producto no encontrado.\n";
        pausar();
        return;
    }

    cout << "  Producto: " << productos[idx].nombre << "\n";
    cout << "  ¿Confirma la eliminación? (1=Sí / 2=No): ";
    int conf = leerEnteroSeguro("", 1, 2);

    if (conf == 1) {
        productos[idx].activo = false;
        guardarProductos();
        cout << "  [OK] Producto desactivado exitosamente.\n";
    } else {
        cout << "  [INFO] Operación cancelada.\n";
    }
    pausar();
}

void menuProductos() {
    int opcion;
    do {
        mostrarEncabezado("MÓDULO 1 — GESTIÓN DE PRODUCTOS");
        cout << "  [1] Registrar producto\n";
        cout << "  [2] Listar productos\n";
        cout << "  [3] Buscar por código\n";
        cout << "  [4] Buscar por nombre\n";
        cout << "  [5] Actualizar stock\n";
        cout << "  [6] Modificar precio\n";
        cout << "  [7] Eliminar/Desactivar producto\n";
        cout << "  [0] Volver al menú principal\n\n";
        opcion = leerEnteroSeguro("Seleccione una opción: ", 0, 7);

        switch (opcion) {
            case 1: registrarProducto();      break;
            case 2: listarProductos();         break;
            case 3: buscarProductoPorCodigo(); break;
            case 4: buscarProductoPorNombre(); break;
            case 5: actualizarStock();         break;
            case 6: modificarPrecio();         break;
            case 7: eliminarProducto();        break;
        }
    } while (opcion != 0);
}

// ============================================================
//   IMPLEMENTACIÓN: MÓDULO 2 — PROCESO DE VENTA
// ============================================================

double calcularDescuento(double subtotal, int totalArticulos) {
    double descuento = 0.0;

    // Descuento por monto
    if (subtotal > 500.0) {
        descuento += subtotal * 0.05;   // 5 % por superar Q500
        cout << "  >> Descuento por compra mayor a Q500: 5% aplicado.\n";
    }

    // Descuento adicional si total de artículos es múltiplo de 5
    if (totalArticulos % 5 == 0 && totalArticulos > 0) {
        double bonoPorcentaje = 0.03;
        descuento += subtotal * bonoPorcentaje;
        cout << "  >> Bono especial: cantidad total múltiplo de 5 → +"
             << bonoPorcentaje * 100 << "% adicional.\n";
    }

    return descuento;
}

void mostrarResumenVenta(const Venta& v) {
    mostrarLineaSeparadora();
    cout << "  === RESUMEN DE VENTA #" << v.idVenta << " ===\n";
    cout << "  Fecha: " << setfill('0') << setw(2) << v.dia << "/"
         << setw(2) << v.mes << "/" << v.anio
         << "  Hora: " << setw(2) << v.hora << ":" << setw(2) << v.minuto
         << setfill(' ') << "\n\n";

    cout << "  " << left << setw(25) << "PRODUCTO"
         << setw(6) << "CANT"
         << setw(12) << "P.UNIT"
         << setw(12) << "SUBTOTAL" << "\n";
    cout << "  " << string(55, '-') << "\n";

    for (int i = 0; i < v.numDetalles; i++) {
        const DetalleVenta& d = v.detalles[i];
        cout << "  " << left
             << setw(25) << d.nombreProducto
             << setw(6)  << d.cantidad
             << "Q" << setw(11) << fixed << setprecision(2) << d.precioUnitario
             << "Q" << fixed << setprecision(2) << d.subtotalDetalle << "\n";
    }

    cout << "  " << string(55, '-') << "\n";
    cout << "  Total artículos : " << v.totalArticulos << "\n";
    cout << "  Subtotal        : Q" << fixed << setprecision(2) << v.subtotal      << "\n";
    cout << "  Descuento       : Q" << fixed << setprecision(2) << v.descuento     << "\n";
    cout << "  IVA (12%)       : Q" << fixed << setprecision(2) << v.iva           << "\n";
    cout << "  TOTAL A PAGAR   : Q" << fixed << setprecision(2) << v.total         << "\n";
    mostrarLineaSeparadora();
}

void crearVenta() {
    mostrarEncabezado("MÓDULO 2 — CREAR NUEVA VENTA");

    if (numProductos == 0) {
        cout << "  [ERROR] No hay productos registrados.\n";
        pausar();
        return;
    }

    Venta v;
    v.numDetalles    = 0;
    v.subtotal       = 0.0;
    v.totalArticulos = 0;
    v.idVenta        = numVentas + 1;

    // Capturar fecha/hora actual
    time_t ahora    = time(nullptr);
    tm*    tiempoTm = localtime(&ahora);
    v.dia   = tiempoTm->tm_mday;
    v.mes   = tiempoTm->tm_mon + 1;
    v.anio  = tiempoTm->tm_year + 1900;
    v.hora  = tiempoTm->tm_hour;
    v.minuto = tiempoTm->tm_min;

    char agregarMas = 's';

    do {
        if (v.numDetalles >= MAX_DETALLES) {
            cout << "  [INFO] Límite de productos por venta alcanzado.\n";
            break;
        }

        listarProductos();
        mostrarEncabezado("AGREGAR PRODUCTO A VENTA #" + to_string(v.idVenta));

        int codigo = leerEnteroSeguro("Código del producto: ", 1, 9999);
        int idx    = encontrarProductoPorCodigo(codigo);

        if (idx == -1) {
            cout << "  [ERROR] Producto no encontrado.\n";
            pausar();
            continue;
        }

        Producto& p = productos[idx];
        cout << "  Producto: " << p.nombre
             << " | Stock disponible: " << p.stock
             << " | Precio: Q" << fixed << setprecision(2) << p.precio << "\n";

        if (p.stock == 0) {
            cout << "  [ERROR] Sin stock disponible.\n";
            pausar();
            continue;
        }

        int cantidad = leerEnteroSeguro("Cantidad: ", 1, p.stock);

        // Verificar stock suficiente
        if (cantidad > p.stock) {
            cout << "  [ERROR] Stock insuficiente. Disponible: " << p.stock << "\n";
            pausar();
            continue;
        }

        // Agregar detalle
        DetalleVenta& det = v.detalles[v.numDetalles];
        det.codigoProducto  = p.codigo;
        strncpy(det.nombreProducto, p.nombre, 59);
        det.nombreProducto[59] = '\0';
        det.cantidad        = cantidad;
        det.precioUnitario  = p.precio;
        det.subtotalDetalle = round(p.precio * cantidad * 100.0) / 100.0;

        v.subtotal       += det.subtotalDetalle;
        v.totalArticulos += cantidad;
        v.numDetalles++;

        // Descontar stock inmediatamente
        p.stock          -= cantidad;
        p.totalVendido   += cantidad;

        cout << "  [OK] Agregado: " << p.nombre << " x" << cantidad
             << " = Q" << fixed << setprecision(2) << det.subtotalDetalle << "\n";
        cout << "  Subtotal acumulado: Q" << fixed << setprecision(2) << v.subtotal << "\n\n";

        cout << "  ¿Agregar otro producto? (s/n): ";
        string resp;
        getline(cin, resp);
        agregarMas = resp.empty() ? 'n' : tolower(resp[0]);

    } while (agregarMas == 's' && v.numDetalles < MAX_DETALLES);

    if (v.numDetalles == 0) {
        cout << "  [INFO] Venta cancelada, no se agregaron productos.\n";
        pausar();
        return;
    }

    // Cálculos finales
    cout << "\n  Calculando totales...\n\n";
    v.descuento = calcularDescuento(v.subtotal, v.totalArticulos);

    double baseGravable = v.subtotal - v.descuento;
    v.iva   = round(baseGravable * IVA * 100.0) / 100.0;
    v.total = round((baseGravable + v.iva) * 100.0) / 100.0;

    mostrarResumenVenta(v);

    // Confirmar venta
    int confirmar = leerEnteroSeguro("¿Confirmar venta? (1=Sí / 2=Cancelar): ", 1, 2);
    if (confirmar == 2) {
        // Revertir cambios de stock
        for (int i = 0; i < v.numDetalles; i++) {
            int idx2 = encontrarProductoPorCodigo(v.detalles[i].codigoProducto);
            if (idx2 != -1) {
                productos[idx2].stock        += v.detalles[i].cantidad;
                productos[idx2].totalVendido -= v.detalles[i].cantidad;
            }
        }
        cout << "  [INFO] Venta cancelada. Stock revertido.\n";
        pausar();
        return;
    }

    // Guardar venta y productos
    guardarVenta(v);
    guardarProductos();

    cout << "\n  [OK] Venta #" << v.idVenta << " guardada exitosamente.\n";
    cout << "  Total cobrado: Q" << fixed << setprecision(2) << v.total << "\n";
    pausar();
}

void menuVentas() {
    int opcion;
    do {
        mostrarEncabezado("MÓDULO 2 — PROCESO DE VENTA");
        cout << "  [1] Crear nueva venta\n";
        cout << "  [0] Volver al menú principal\n\n";
        opcion = leerEnteroSeguro("Seleccione una opción: ", 0, 1);
        if (opcion == 1) crearVenta();
    } while (opcion != 0);
}

// ============================================================
//   IMPLEMENTACIÓN: MÓDULO 3 — REPORTES
// ============================================================

// Ordenamiento Bubble Sort por precio
void ordenarProductosPorPrecio(bool ascendente) {
    // Crear copia temporal de índices activos
    int indices[MAX_PRODUCTOS];
    int n = 0;
    for (int i = 0; i < numProductos; i++)
        if (productos[i].activo) indices[n++] = i;

    // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool intercambiar = ascendente
                ? productos[indices[j]].precio > productos[indices[j+1]].precio
                : productos[indices[j]].precio < productos[indices[j+1]].precio;
            if (intercambiar) swap(indices[j], indices[j+1]);
        }
    }

    cout << "\n  Ordenado por precio " << (ascendente ? "ASCENDENTE" : "DESCENDENTE") << ":\n";
    cout << "  " << left << setw(6) << "COD"
         << setw(25) << "NOMBRE"
         << setw(12) << "PRECIO"
         << setw(8)  << "STOCK" << "\n";
    cout << "  " << string(51, '-') << "\n";
    for (int i = 0; i < n; i++) {
        Producto& p = productos[indices[i]];
        cout << "  " << left << setw(6) << p.codigo
             << setw(25) << p.nombre
             << "Q" << setw(11) << fixed << setprecision(2) << p.precio
             << setw(8) << p.stock << "\n";
    }
}

// Ordenamiento Selection Sort por stock
void ordenarProductosPorStock(bool ascendente) {
    int indices[MAX_PRODUCTOS];
    int n = 0;
    for (int i = 0; i < numProductos; i++)
        if (productos[i].activo) indices[n++] = i;

    // Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int seleccionado = i;
        for (int j = i + 1; j < n; j++) {
            bool esMinimo = ascendente
                ? productos[indices[j]].stock < productos[indices[seleccionado]].stock
                : productos[indices[j]].stock > productos[indices[seleccionado]].stock;
            if (esMinimo) seleccionado = j;
        }
        if (seleccionado != i) swap(indices[i], indices[seleccionado]);
    }

    cout << "\n  Ordenado por stock " << (ascendente ? "ASCENDENTE" : "DESCENDENTE") << ":\n";
    cout << "  " << left << setw(6) << "COD"
         << setw(25) << "NOMBRE"
         << setw(8)  << "STOCK"
         << setw(12) << "PRECIO" << "\n";
    cout << "  " << string(51, '-') << "\n";
    for (int i = 0; i < n; i++) {
        Producto& p = productos[indices[i]];
        cout << "  " << left << setw(6) << p.codigo
             << setw(25) << p.nombre
             << setw(8)  << p.stock
             << "Q" << fixed << setprecision(2) << p.precio << "\n";
    }
}

// Insertion Sort por ventas acumuladas
void ordenarProductosPorVentas() {
    int indices[MAX_PRODUCTOS];
    int n = 0;
    for (int i = 0; i < numProductos; i++)
        if (productos[i].activo) indices[n++] = i;

    // Insertion Sort descendente por totalVendido
    for (int i = 1; i < n; i++) {
        int key = indices[i];
        int j   = i - 1;
        while (j >= 0 && productos[indices[j]].totalVendido < productos[key].totalVendido) {
            indices[j + 1] = indices[j];
            j--;
        }
        indices[j + 1] = key;
    }

    cout << "\n  Ordenado por VENTAS ACUMULADAS (mayor a menor):\n";
    cout << "  " << left << setw(6)  << "COD"
         << setw(25) << "NOMBRE"
         << setw(10) << "VENDIDO"
         << setw(8)  << "STOCK" << "\n";
    cout << "  " << string(49, '-') << "\n";
    for (int i = 0; i < n; i++) {
        Producto& p = productos[indices[i]];
        cout << "  " << left << setw(6)  << p.codigo
             << setw(25) << p.nombre
             << setw(10) << p.totalVendido
             << setw(8)  << p.stock << "\n";
    }
}

void reporteStockBajo() {
    mostrarEncabezado("REPORTE — PRODUCTOS CON MENOR STOCK");

    int umbral = leerEnteroSeguro("Mostrar productos con stock menor o igual a: ", 0, 99999);

    bool hayResultados = false;
    cout << "\n  " << left
         << setw(6)  << "COD"
         << setw(25) << "NOMBRE"
         << setw(8)  << "STOCK"
         << setw(12) << "PRECIO" << "\n";
    mostrarLineaSeparadora();

    for (int i = 0; i < numProductos; i++) {
        if (!productos[i].activo) continue;
        if (productos[i].stock <= umbral) {
            hayResultados = true;
            cout << "  " << left
                 << setw(6)  << productos[i].codigo
                 << setw(25) << productos[i].nombre
                 << setw(8)  << productos[i].stock
                 << "Q" << fixed << setprecision(2) << productos[i].precio << "\n";
        }
    }

    if (!hayResultados)
        cout << "  No hay productos con stock <= " << umbral << ".\n";

    pausar();
}

void reporteProductosMasVendidos() {
    mostrarEncabezado("REPORTE — PRODUCTOS MÁS VENDIDOS");
    ordenarProductosPorVentas();
    pausar();
}

void reporteVentasDia() {
    mostrarEncabezado("REPORTE — VENTAS TOTALES DEL DÍA");

    time_t ahora    = time(nullptr);
    tm*    hoy      = localtime(&ahora);
    int    diaHoy   = hoy->tm_mday;
    int    mesHoy   = hoy->tm_mon + 1;
    int    anioHoy  = hoy->tm_year + 1900;

    double totalDia   = 0.0;
    int    numVentasDia = 0;

    cout << "  Fecha: " << setfill('0') << setw(2) << diaHoy << "/"
         << setw(2) << mesHoy << "/" << anioHoy << setfill(' ') << "\n\n";
    cout << "  " << left << setw(8)  << "VENTA #"
         << setw(10) << "HORA"
         << setw(10) << "ART."
         << setw(12) << "TOTAL" << "\n";
    cout << "  " << string(40, '-') << "\n";

    for (int i = 0; i < numVentas; i++) {
        if (ventas[i].dia == diaHoy && ventas[i].mes == mesHoy &&
            ventas[i].anio == anioHoy) {
            numVentasDia++;
            totalDia += ventas[i].total;
            cout << "  " << left
                 << setw(8) << ventas[i].idVenta
                 << setfill('0') << setw(2) << ventas[i].hora << ":"
                 << setw(2) << ventas[i].minuto << setfill(' ')
                 << "    "
                 << setw(10) << ventas[i].totalArticulos
                 << "Q" << fixed << setprecision(2) << ventas[i].total << "\n";
        }
    }

    cout << "\n  " << string(40, '-') << "\n";
    cout << "  Total ventas del día : " << numVentasDia << "\n";
    cout << "  Monto total del día  : Q" << fixed << setprecision(2) << totalDia << "\n";

    pausar();
}

void reporteVentasPorMes() {
    mostrarEncabezado("REPORTE — VENTAS POR MES (MATRIZ)");

    cargarMatrizVentas();

    const string MESES[12] = {
        "Enero","Febrero","Marzo","Abril","Mayo","Junio",
        "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
    };

    for (int m = 0; m < 12; m++) {
        double totalMes = 0.0;
        bool hayVentas  = false;

        // Revisar si hay ventas en este mes
        for (int d = 0; d < 31; d++)
            if (ventasPorMes[m][d] > 0.0) hayVentas = true;

        if (!hayVentas) continue;

        cout << "  *** " << MESES[m] << " ***\n";
        for (int d = 0; d < 31; d++) {
            if (ventasPorMes[m][d] > 0.0) {
                cout << "    Día " << setw(2) << (d+1) << ": Q"
                     << fixed << setprecision(2) << ventasPorMes[m][d] << "\n";
                totalMes += ventasPorMes[m][d];
            }
        }
        cout << "  Total " << MESES[m] << ": Q"
             << fixed << setprecision(2) << totalMes << "\n\n";
    }

    pausar();
}

void menuReportes() {
    int opcion;
    do {
        mostrarEncabezado("MÓDULO 3 — REPORTES");
        cout << "  [1] Productos con menor stock\n";
        cout << "  [2] Productos más vendidos\n";
        cout << "  [3] Ventas totales del día\n";
        cout << "  [4] Ventas por mes (matriz)\n";
        cout << "  [5] Ordenar por precio ascendente\n";
        cout << "  [6] Ordenar por precio descendente\n";
        cout << "  [7] Ordenar por stock ascendente\n";
        cout << "  [8] Ordenar por stock descendente\n";
        cout << "  [9] Ordenar por ventas acumuladas\n";
        cout << "  [0] Volver al menú principal\n\n";
        opcion = leerEnteroSeguro("Seleccione una opción: ", 0, 9);

        switch (opcion) {
            case 1: reporteStockBajo();          break;
            case 2: reporteProductosMasVendidos(); break;
            case 3: reporteVentasDia();           break;
            case 4: reporteVentasPorMes();        break;
            case 5:
                mostrarEncabezado("ORDENAR POR PRECIO ASCENDENTE");
                ordenarProductosPorPrecio(true);
                pausar(); break;
            case 6:
                mostrarEncabezado("ORDENAR POR PRECIO DESCENDENTE");
                ordenarProductosPorPrecio(false);
                pausar(); break;
            case 7:
                mostrarEncabezado("ORDENAR POR STOCK ASCENDENTE");
                ordenarProductosPorStock(true);
                pausar(); break;
            case 8:
                mostrarEncabezado("ORDENAR POR STOCK DESCENDENTE");
                ordenarProductosPorStock(false);
                pausar(); break;
            case 9:
                mostrarEncabezado("ORDENAR POR VENTAS ACUMULADAS");
                ordenarProductosPorVentas();
                pausar(); break;
        }
    } while (opcion != 0);
}

// ============================================================
//   IMPLEMENTACIÓN: MÓDULO 4 — UTILIDADES DEL SISTEMA
// ============================================================

void exportarReporteTxt() {
    mostrarEncabezado("EXPORTAR REPORTE A ARCHIVO TXT");

    try {
        ofstream archivo(ARCHIVO_REPORTE);
        if (!archivo.is_open())
            throw runtime_error("No se pudo crear " + ARCHIVO_REPORTE);

        time_t ahora   = time(nullptr);
        string fechaStr = string(ctime(&ahora));

        archivo << "====================================================\n";
        archivo << "  SISTEMA DE GESTIÓN DE VENTAS E INVENTARIO\n";
        archivo << "  Reporte generado: " << fechaStr;
        archivo << "====================================================\n\n";

        // Productos activos
        archivo << "--- INVENTARIO DE PRODUCTOS ---\n";
        archivo << left << setw(6)  << "COD"
                << setw(25) << "NOMBRE"
                << setw(12) << "PRECIO"
                << setw(8)  << "STOCK"
                << setw(8)  << "VENDIDO" << "\n";
        archivo << string(59, '-') << "\n";

        for (int i = 0; i < numProductos; i++) {
            if (!productos[i].activo) continue;
            archivo << left << setw(6)  << productos[i].codigo
                    << setw(25) << productos[i].nombre
                    << "Q" << setw(11) << fixed << setprecision(2) << productos[i].precio
                    << setw(8)  << productos[i].stock
                    << setw(8)  << productos[i].totalVendido << "\n";
        }

        // Resumen de ventas
        archivo << "\n--- RESUMEN DE VENTAS ---\n";
        archivo << "Total de ventas registradas: " << numVentas << "\n";
        double totalGeneral = 0.0;
        for (int i = 0; i < numVentas; i++) totalGeneral += ventas[i].total;
        archivo << "Monto total acumulado: Q" << fixed << setprecision(2) << totalGeneral << "\n";

        // Ventas por mes
        cargarMatrizVentas();
        const string MESES[12] = {
            "Enero","Febrero","Marzo","Abril","Mayo","Junio",
            "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
        };
        archivo << "\n--- VENTAS POR MES ---\n";
        for (int m = 0; m < 12; m++) {
            double totalMes = 0.0;
            for (int d = 0; d < 31; d++) totalMes += ventasPorMes[m][d];
            if (totalMes > 0.0)
                archivo << MESES[m] << ": Q" << fixed << setprecision(2) << totalMes << "\n";
        }

        archivo << "\n====================================================\n";
        archivo << "  Fin del reporte.\n";
        archivo << "====================================================\n";
        archivo.close();

        cout << "  [OK] Reporte exportado exitosamente a: " << ARCHIVO_REPORTE << "\n";
    } catch (const exception& e) {
        cout << "  [ERROR] " << e.what() << "\n";
    }

    pausar();
}

void reiniciarInventario() {
    mostrarEncabezado("REINICIAR INVENTARIO");

    cout << "  ADVERTENCIA: Esta acción eliminará TODOS los productos\n";
    cout << "  y ventas registradas. Esta acción es IRREVERSIBLE.\n\n";
    cout << "  Escriba CONFIRMAR para continuar: ";
    string confirmacion;
    getline(cin, confirmacion);

    if (confirmacion == "CONFIRMAR") {
        numProductos = 0;
        numVentas    = 0;
        guardarProductos();

        // Limpiar archivo de ventas
        ofstream archivoVentas(ARCHIVO_VENTAS, ios::binary | ios::trunc);
        archivoVentas.write(reinterpret_cast<char*>(&numVentas), sizeof(int));
        archivoVentas.close();

        cout << "\n  [OK] Inventario reiniciado exitosamente.\n";
    } else {
        cout << "\n  [INFO] Operación cancelada. No se realizaron cambios.\n";
    }
    pausar();
}

void mostrarEstadisticasGenerales() {
    mostrarEncabezado("ESTADÍSTICAS GENERALES DEL SISTEMA");

    // Calcular estadísticas
    int    totalProductosActivos  = 0;
    int    totalProductosAgotados = 0;
    double valorTotalInventario   = 0.0;
    double productoMasCaro        = 0.0;
    double productoMasBarato      = -1.0;
    double totalVentasAcumuladas  = 0.0;
    int    totalArticulosVendidos = 0;
    string nombreMasCaro, nombreMasBarato;

    for (int i = 0; i < numProductos; i++) {
        if (!productos[i].activo) continue;
        totalProductosActivos++;
        valorTotalInventario += productos[i].precio * productos[i].stock;
        totalArticulosVendidos += productos[i].totalVendido;

        if (productos[i].stock == 0) totalProductosAgotados++;

        if (productos[i].precio > productoMasCaro) {
            productoMasCaro = productos[i].precio;
            nombreMasCaro   = string(productos[i].nombre);
        }
        if (productoMasBarato < 0 || productos[i].precio < productoMasBarato) {
            productoMasBarato = productos[i].precio;
            nombreMasBarato   = string(productos[i].nombre);
        }
    }

    for (int i = 0; i < numVentas; i++)
        totalVentasAcumuladas += ventas[i].total;

    // Promedios
    double promedioVenta = (numVentas > 0) ? totalVentasAcumuladas / numVentas : 0.0;

    cout << "  INVENTARIO:\n";
    cout << "  Productos activos      : " << totalProductosActivos  << "\n";
    cout << "  Productos agotados     : " << totalProductosAgotados << "\n";
    cout << "  Valor total inventario : Q" << fixed << setprecision(2) << valorTotalInventario << "\n";
    if (productoMasCaro > 0) {
        cout << "  Producto más caro      : " << nombreMasCaro
             << " (Q" << fixed << setprecision(2) << productoMasCaro << ")\n";
        cout << "  Producto más barato    : " << nombreMasBarato
             << " (Q" << fixed << setprecision(2) << productoMasBarato << ")\n";
    }

    cout << "\n  VENTAS:\n";
    cout << "  Total ventas realizadas: " << numVentas << "\n";
    cout << "  Monto total acumulado  : Q" << fixed << setprecision(2) << totalVentasAcumuladas << "\n";
    cout << "  Promedio por venta     : Q" << fixed << setprecision(2) << promedioVenta << "\n";
    cout << "  Total artículos vend.  : " << totalArticulosVendidos << "\n";

    pausar();
}

void menuUtilidades() {
    int opcion;
    do {
        mostrarEncabezado("MÓDULO 4 — UTILIDADES DEL SISTEMA");
        cout << "  [1] Exportar reporte a .txt\n";
        cout << "  [2] Reiniciar inventario\n";
        cout << "  [3] Estadísticas generales\n";
        cout << "  [0] Volver al menú principal\n\n";
        opcion = leerEnteroSeguro("Seleccione una opción: ", 0, 3);

        switch (opcion) {
            case 1: exportarReporteTxt();        break;
            case 2: reiniciarInventario();        break;
            case 3: mostrarEstadisticasGenerales(); break;
        }
    } while (opcion != 0);
}

// ============================================================
//   MENÚ PRINCIPAL Y BIENVENIDA
// ============================================================

void mostrarBienvenida() {
    limpiarPantalla();
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    cout << "  ║       SISTEMA DE GESTIÓN DE VENTAS E INVENTARIO          ║\n";
    cout << "  ║                   Proyecto Final C++                     ║\n";
    cout << "  ║                                                          ║\n";
    cout << "  ║   Autor : José Daniel Real García                        ║\n";
    cout << "  ║   Carnet: 9941 - 25 - 837                                ║\n";
    cout << "  ║   Curso : Programación I                                 ║\n";
    cout << "  ║   Año   : 2026                                           ║\n";
    cout << "  ╚══════════════════════════════════════════════════════════╝\n\n";
    cout << "  Cargando datos del sistema...\n";

    cargarProductos();
    cargarVentas();
    cargarMatrizVentas();

    cout << "  " << numProductos << " producto(s) cargado(s).\n";
    cout << "  " << numVentas    << " venta(s) cargada(s).\n\n";
    pausar();
}

void menuPrincipal() {
    int opcion;
    do {
        mostrarEncabezado("MENÚ PRINCIPAL");
        cout << "  [1] Módulo 1 — Gestión de Productos\n";
        cout << "  [2] Módulo 2 — Proceso de Venta\n";
        cout << "  [3] Módulo 3 — Reportes\n";
        cout << "  [4] Módulo 4 — Utilidades del Sistema\n";
        cout << "  [0] Salir del sistema\n\n";
        opcion = leerEnteroSeguro("Seleccione una opción: ", 0, 4);

        switch (opcion) {
            case 1: menuProductos();   break;
            case 2: menuVentas();      break;
            case 3: menuReportes();    break;
            case 4: menuUtilidades();  break;
            case 0:
                limpiarPantalla();
                cout << "\n  Gracias por usar el Sistema de Gestión de Tienda.\n";
                cout << "  ¡Hasta pronto!\n\n";
                break;
        }
    } while (opcion != 0);
}

// ============================================================
//   FUNCIÓN PRINCIPAL
// ============================================================
int main() {
    // Configurar locale para caracteres especiales (Windows)
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    mostrarBienvenida();
    menuPrincipal();
    return 0;
}
