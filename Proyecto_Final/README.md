# Sistema de Gestión de Ventas e Inventario para Tienda

> Proyecto Final de Programación — C++  
> Autor: **José Daniel Real García**  
> Carnet: **9941 - 25 - 837**  
> Curso: Programación I
> Año: 2026

---

## Descripción del Proyecto

Sistema de consola desarrollado en **C++** que permite administrar productos, ventas e inventario de una tienda. Implementa persistencia de datos mediante **archivos binarios**, programación estructurada, búsqueda, ordenamiento y manejo de excepciones.

---

## Estructura del Proyecto

```
tienda_cpp/
│
├── main.cpp              ← Código fuente principal (único archivo)
├── README.md             ← Este archivo
│
├── .vscode/
│   ├── tasks.json        ← Tareas de compilación para VS Code
│   ├── launch.json       ← Configuración del depurador
│   └── c_cpp_properties.json
│
├── productos.dat         ← Archivo binario de productos (generado al ejecutar)
├── ventas.dat            ← Archivo binario de ventas (generado al ejecutar)
├── reporte.txt           ← Reporte exportado (generado desde el sistema)
│
└── documentacion.pdf     ← Documentación del proyecto
```

---

## Requisitos Previos

### Windows
- **Compilador**: MinGW-w64 con g++ (C++17 o superior)
- Descarga: https://www.mingw-w64.org/downloads/
- **Editor**: Visual Studio Code con extensión **C/C++ (Microsoft)**

### Linux / macOS
- **Compilador**: g++ (ya incluido o instala con `sudo apt install g++`)
- **Editor**: Visual Studio Code con extensión **C/C++ (Microsoft)**

---

## Cómo Compilar y Ejecutar

Dado que el proyecto incluye un archivo para inyectar datos de prueba (`generar_datos_prueba.cpp`) y el sistema principal (`main.cpp`), la compilación consta de dos pasos. Ambos programas se compilan y ejecutan por separado para evitar conflictos de múltiples funciones `main`.

### Opción 1 — Desde la Terminal Integrada de VS Code (Recomendado)

1. Abre la carpeta del proyecto en VS Code (`Archivo → Abrir Carpeta`).
2. Abre la terminal integrada presionando `` Ctrl + ` `` (o `Ctrl + ñ` en teclados en español).
3. **Paso A: Generar los datos de prueba** *(Se hace la primera vez o si quieres reiniciar los datos de prueba)*
   ```bash
   # Compilar el generador
   g++ generar_datos_prueba.cpp -o GenerarDatos
   
   # Ejecutar el generador (Windows)
   .\GenerarDatos.exe
   
   # Ejecutar el generador (Linux / macOS)
   ./GenerarDatos
   ```
4. **Paso B: Compilar y ejecutar el Sistema Principal**
   Una vez que se haya creado el archivo `productos.dat`, compila y arranca tu tienda:
   ```bash
   # Compilar el sistema principal
   g++ -std=c++17 -Wall main.cpp -o SistemaTienda
   
   # Ejecutar el sistema (Windows)
   .\SistemaTienda.exe
   
   # Ejecutar el sistema (Linux / macOS)
   ./SistemaTienda
   ```

> **Nota sobre VS Code:** Si deseas usar `F5` para depurar o `Ctrl + Shift + B` para compilar automáticamente, deberás configurar tus archivos `tasks.json` y `launch.json` para que apunten específicamente a `main.cpp` y generen `SistemaTienda.exe`.

### Opción 2 — Desde una Terminal Externa (PowerShell, CMD o Bash)

Si prefieres usar una consola externa, navega hasta la carpeta de tu proyecto y ejecuta la misma secuencia:

```bash
# 1. Compilar y ejecutar el generador de datos
g++ generar_datos_prueba.cpp -o GenerarDatos
.\GenerarDatos.exe   # En Linux/macOS usar: ./GenerarDatos

# 2. Compilar y ejecutar el sistema de la tienda
g++ -std=c++17 -Wall main.cpp -o SistemaTienda
.\SistemaTienda.exe  # En Linux/macOS usar: ./SistemaTienda
```

---

## Módulos del Sistema

### Módulo 1 — Gestión de Productos
| Función | Descripción |
|--------|-------------|
| Registrar producto | Agrega un nuevo producto con código único |
| Listar productos | Muestra todos los productos activos |
| Buscar por código | Búsqueda directa por código numérico |
| Buscar por nombre | Búsqueda secuencial parcial insensible a mayúsculas |
| Actualizar stock | Modifica las unidades disponibles |
| Modificar precio | Cambia el precio unitario |
| Eliminar producto | Desactiva el producto (eliminación lógica) |

### Módulo 2 — Proceso de Venta
| Función | Descripción |
|--------|-------------|
| Crear venta | Agrega múltiples productos a una venta |
| Validar stock | Verifica disponibilidad antes de vender |
| Aplicar IVA | 12% sobre la base gravable |
| Descuento por monto | 5% si subtotal > Q500 |
| Bono especial | 3% adicional si cantidad total de artículos es múltiplo de 5 |
| Persistencia | Guarda la venta en `ventas.dat` y descuenta stock |

### Módulo 3 — Reportes
| Función | Descripción |
|--------|-------------|
| Stock bajo | Filtra productos con stock ≤ umbral definido |
| Más vendidos | Ordenados por unidades vendidas (Insertion Sort) |
| Ventas del día | Totales de la fecha actual |
| Ventas por mes | Matriz `ventasPorMes[12][31]` acumulada |
| Ordenar por precio | Ascendente/Descendente (Bubble Sort) |
| Ordenar por stock | Ascendente/Descendente (Selection Sort) |

### Módulo 4 — Utilidades
| Función | Descripción |
|--------|-------------|
| Exportar .txt | Genera `reporte.txt` con inventario y resumen de ventas |
| Reiniciar inventario | Borra todos los datos (requiere confirmación escrita) |
| Estadísticas | Totales, promedios y extremos del sistema |

---

## Estructuras de Datos

```cpp
struct Producto {
    int    codigo;           // Identificador único
    char   nombre[60];       // Nombre del producto
    char   categoria[30];    // Categoría del producto
    double precio;           // Precio unitario en Quetzales
    int    stock;            // Unidades disponibles
    int    totalVendido;     // Acumulado de unidades vendidas
    bool   activo;           // Estado (eliminación lógica)
};

struct DetalleVenta {
    int    codigoProducto;   // Referencia al producto
    char   nombreProducto[60];
    int    cantidad;
    double precioUnitario;
    double subtotalDetalle;
};

struct Venta {
    int          idVenta;           // ID incremental
    int          dia, mes, anio;    // Fecha
    int          hora, minuto;      // Hora
    DetalleVenta detalles[20];      // Máx. 20 productos por venta
    int          numDetalles;
    double       subtotal;
    double       descuento;
    double       iva;
    double       total;
    int          totalArticulos;
};
```

---

## Algoritmos Implementados

### Búsqueda
- **Secuencial por nombre**: Recorre el arreglo comparando subcadenas (insensible a mayúsculas).
- **Por código**: Búsqueda secuencial con retorno inmediato del índice.

### Ordenamiento
| Algoritmo | Aplicación |
|-----------|-----------|
| **Bubble Sort** | Ordenar productos por precio |
| **Selection Sort** | Ordenar productos por stock |
| **Insertion Sort** | Ordenar productos por ventas acumuladas |

---

## Archivos Binarios

| Archivo | Contenido |
|---------|-----------|
| `productos.dat` | `int numProductos` + arreglo de `Producto[]` |
| `ventas.dat` | `int numVentas` + arreglo de `Venta[]` |

Los archivos se crean automáticamente al guardar por primera vez y persisten entre ejecuciones.

---

## Manejo de Errores (try/catch)

El sistema usa bloques `try/catch` para:
- Entradas no numéricas del usuario
- Valores fuera de rango
- Apertura/escritura de archivos binarios
- Archivos corruptos al cargar

---

## Fórmulas y Lógica Comercial

```
Descuento por monto     = subtotal × 5%    si subtotal > Q500
Bono por cantidad       = subtotal × 3%    si totalArticulos % 5 == 0
Base gravable           = subtotal − descuento
IVA                     = base_gravable × 12%
Total                   = base_gravable + IVA  (redondeado a 2 decimales)
```

---

## Evidencias

Ver carpeta `/evidencias/` con capturas de pantalla de:
1. Pantalla de bienvenida con nombre del estudiante
2. Registro de productos
3. Proceso de venta completo
4. Reportes generados
5. Búsquedas realizadas
6. Persistencia entre ejecuciones (archivos `.dat`)

---

## Notas de Desarrollo

- El sistema usa **dos archivos** `main.cpp` y `generar_datos_prueba.cpp` para facilitar la entrega.
- Los archivos `.dat` se generan en el **mismo directorio** donde se ejecuta el programa.
- Compilado y probado con **g++ 13.x** en Windows (MinGW) y Linux.
- Usa `std=c++17` por las funciones de `<algorithm>` y manejo moderno de strings.
