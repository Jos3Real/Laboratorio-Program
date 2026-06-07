// Script auxiliar para generar archivos .dat de prueba
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// IMPORTANTE: Este valor DEBE ser idéntico a MAX_DETALLES en main.cpp
const int MAX_DETALLES = 20;

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
    int          dia, mes, anio, hora, minuto;
    DetalleVenta detalles[MAX_DETALLES];   // sincronizado con main.cpp
    int          numDetalles;
    double       subtotal;
    double       descuento;
    double       iva;
    double       total;
    int          totalArticulos;
};

int main() {
    // Crear productos de prueba
    Producto prods[8];
    int n = 8;

    auto setP = [&](int i, int cod, const char* nom, const char* cat, double precio, int stock, int vendido) {
        prods[i].codigo = cod;
        strncpy(prods[i].nombre, nom, 59);   prods[i].nombre[59] = 0;
        strncpy(prods[i].categoria, cat, 29); prods[i].categoria[29] = 0;
        prods[i].precio = precio;
        prods[i].stock  = stock;
        prods[i].totalVendido = vendido;
        prods[i].activo = true;
    };

    setP(0, 101, "Coca Cola 600ml",       "Bebidas",      7.50,  90,  10);
    setP(1, 102, "Pan Bimbo Grande",       "Panificacion", 15.00, 47,   3);
    setP(2, 103, "Aceite Ideal 1L",        "Aceites",      28.50, 30,   0);
    setP(3, 104, "Arroz Toro 1LB",         "Granos",        5.00, 200,   0);
    setP(4, 105, "Frijoles Negros 1LB",    "Granos",        6.50, 150,   0);
    setP(5, 201, "Jabon Palmolive",        "Higiene",       9.75, 60,   0);
    setP(6, 202, "Shampoo Head Shoulders", "Higiene",      35.00, 25,   0);
    setP(7, 301, "Papel Higienico Suave",  "Hogar",        22.00,  5,   0);

    ofstream fp("productos.dat", ios::binary | ios::trunc);
    fp.write(reinterpret_cast<char*>(&n), sizeof(int));
    fp.write(reinterpret_cast<char*>(prods), sizeof(Producto)*n);
    fp.close();

    // Crear una venta de prueba
    Venta v;
    v.idVenta = 1; v.dia = 6; v.mes = 6; v.anio = 2026; v.hora = 10; v.minuto = 30;
    v.numDetalles = 2; v.totalArticulos = 13;

    v.detalles[0].codigoProducto = 101;
    strncpy(v.detalles[0].nombreProducto, "Coca Cola 600ml", 59);
    v.detalles[0].cantidad = 10; v.detalles[0].precioUnitario = 7.50; v.detalles[0].subtotalDetalle = 75.00;

    v.detalles[1].codigoProducto = 102;
    strncpy(v.detalles[1].nombreProducto, "Pan Bimbo Grande", 59);
    v.detalles[1].cantidad = 3; v.detalles[1].precioUnitario = 15.00; v.detalles[1].subtotalDetalle = 45.00;

    v.subtotal = 120.00; v.descuento = 0.00; v.iva = 14.40; v.total = 134.40;

    int nv = 1;
    ofstream fv("ventas.dat", ios::binary | ios::trunc);
    fv.write(reinterpret_cast<char*>(&nv), sizeof(int));
    fv.write(reinterpret_cast<char*>(&v), sizeof(Venta));
    fv.close();

    cout << "[OK] Archivos productos.dat y ventas.dat generados con datos de prueba.\n";
    cout << "     " << n << " productos | 1 venta de prueba\n";
    return 0;
}