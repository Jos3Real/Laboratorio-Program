# Sistema de Gestión de Productos y Ventas en C++

Este proyecto es el primer módulo funcional de un sistema de gestión desarrollado en C++. Implementa operaciones CRUD (Crear, Leer, Actualizar, Borrar lógicamente) utilizando archivos binarios para garantizar la persistencia de los datos entre diferentes ejecuciones.

## Tecnologías utilizadas
* C++ (Librería Estándar)
* Manejo de Memoria Persistente (`fstream`, archivos `.dat` binarios)

## Requerimientos funcionales implementados
1. **Menú interactivo** estructurado.
2. **Gestión de productos (CRUD):** - Registro de información mediante un `struct Producto`.
   - Listado de inventario activo.
   - Búsqueda por código y por nombre.
   - Modificación de precio y stock.
   - Desactivación de producto (baja lógica).
3. **Proceso de venta:**
   - Validaciones automáticas de stock.
   - Cálculo de Subtotal, IVA (12%) y Total.
   - Descuento automático de las unidades vendidas en el archivo binario.

## Cómo ejecutar
1. Clona el repositorio.
2. Compila el archivo `main.cpp` utilizando tu compilador preferido (G++, MinGW, etc.):
   ```bash
   g++ main.cpp -o sistema