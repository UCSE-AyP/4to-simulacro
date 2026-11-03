# Software Design Document (SDD) — 4to Simulacro 2026
**Módulo 4: Arreglos de Estructuras (AoS) y Algoritmos de Ordenamiento**  
**Universidad Católica de Santiago del Estero — DASS**  
**Cátedra:** Algoritmos y Programación  
**Ciclo Lectivo:** 2026  

---

## 1. Visión General y Objetivos de Evaluación

El presente documento formaliza la arquitectura técnica, estructuras de datos, contratos algorítmicos e invariantes de memoria para el **4to Simulacro de Examen 2026**.

### Modalidad Bimodal Obligatoria
1. **75% Laboratorio de Programación (C++):**
   - Resolución en computadora sobre un arreglo estático de registros (`struct` + array AoS).
   - **Tipos de datos exclusivamente primitivos (`int`, `char`, `double`):** Se evita el tipo `string` para erradicar cualquier conflicto de saltos de línea residuales, desincronización de buffer o necesidad de `cin.ignore()` / `getline()`. Toda la entrada de datos se realiza limpiamente mediante `cin >>`.
   - Implementación de las 6 operaciones fundamentales de la lógica pura (Búsqueda por clave, Inserción con unicidad y corrimiento a derecha, Modificación in-place con clave primaria inmutable, Baja física con compactación del arreglo mediante corrimiento a la izquierda, Ordenamiento Burbuja Mejorada con swap integral y Cálculo Estadístico Seguro con guarda defensiva).
   - Capa de presentación por consola (menús, tablas formateadas con `<iomanip>`, fichas y buffers) **100% pre-implementada** por la cátedra para optimizar el tiempo de examen.
2. **25% Instancia Escrita Individual (Lápiz y Papel):**
   - Trazabilidad manual paso a paso en hoja A4 de un algoritmo clásico de ordenamiento sobre un vector de 5 elementos enteros.
   - Tema 1: **Selección Directa (Selection Sort)** en sentido **Ascendente**.
   - Tema 2: **Inserción Directa (Insertion Sort)** en sentido **Descendente**.

---

## 2. Definición de Temas y Modelos de Datos

### Tema 1: Sistema de Biblioteca Universitaria
- **Entidad:** `Libro`
- **Contexto:** Gestión en RAM del catálogo de ejemplares de la biblioteca, cálculo de antigüedad, clasificación por categorías y liquidación de aranceles de alquiler.
- **Estructura C++:**
```cpp
struct Libro {
    int codigo;            // Clave Primaria unívoca (estrictamente inmutable)
    int anioPub;           // Año de publicación (<= 2026)
    int antiguedad;        // Calculado: 2026 - anioPub
    char categoria;        // 'N' (Nuevo <= 5 años), 'R' (Regular 6-20), 'A' (Antiguo > 20)
    double precioBase;     // Valor base arancelario (> 0)
    double importeAlquiler;// Calculado: precioBase * (1.0 + recargo)
};
```
- **Algoritmo en C++:** Burbuja Mejorada **Ascendente** por `precioBase`.
- **Instancia Escrita:** Selección Directa Ascendente sobre $V = [35, 12, 68, 24, 7]$.

### Tema 2: Stock de Concesionaria Automotriz
- **Entidad:** `Vehiculo`
- **Contexto:** Administración del stock comercial de unidades automotrices, valuación por categoría de antigüedad y descuentos comerciales.
- **Estructura C++:**
```cpp
struct Vehiculo {
    int codigo;            // Clave Primaria unívoca (estrictamente inmutable)
    int anioFabricacion;   // Año de fabricación (<= 2026)
    char categoria;        // 'N' (Nuevo 0-1 años), 'S' (Seminuevo 2-5), 'U' (Usado >= 6)
    double precioLista;    // Valor de lista oficial (> 0)
    double descuentoPorc;  // Porcentaje de descuento comercial (0.0 a 30.0%)
    double precioFinal;    // Calculado: precioLista * (1.0 - desc/100.0) * (1.0 + recargo)
};
```
- **Algoritmo en C++:** Burbuja Mejorada **Descendente** por `precioFinal`.
- **Instancia Escrita:** Inserción Directa Descendente sobre $V = [42, 18, 55, 9, 31]$.

---

## 3. Contratos de Funciones Algorítmicas (Lógica Pura C++)

### 3.1. Búsqueda por Clave Primaria (10%)
- **Firma:** `int buscarPorCodigo(const T arr[], int tam, int codigoBuscado);`
- **Contrato:**
  - Recorrido secuencial respetando el tamaño lógico `tam`.
  - Salida temprana inmediata apenas coincide la clave primaria.
  - Retorno de índice `[0 .. tam-1]` o `-1` (centinela).

### 3.2. Alta / Inserción con Unicidad de Clave (15%)
- **Firma:** `bool insertar(T arr[], int &tam, int capacidad, int pos, const T &nuevo);`
- **Contrato:**
  - Control de capacidad: rechaza si `tam >= capacidad` o `pos < 0` o `pos > tam`.
  - Reutilización obligatoria de búsqueda: rechaza si la clave primaria ya existe (`buscar != -1`).
  - Right-Shift: desplaza desde `tam` hasta `pos` una celda a la derecha.
  - Inserción e incremento: `arr[pos] = nuevo`, `tam++`. Retorna `true`.

### 3.3. Modificación con Clave Inmutable (10%)
- **Firma:** `bool modificar(T arr[], int tam, const T &actualizado);`
- **Contrato:**
  - Reutiliza la búsqueda para hallar la posición de memoria.
  - Muta *in-place* los campos de datos y atributos derivados.
  - **Invariante:** La clave primaria no se modifica bajo ninguna circunstancia.
  - Retorna `true` si se modificó o `false` si no se encontró.

### 3.4. Baja Física con Compactación del Arreglo mediante Corrimiento a la Izquierda (15%)
- **Firma:** `bool darDeBajaFisica(T arr[], int &tam, int codigoABorrar);`
- **Contrato:**
  - Reutiliza la búsqueda para hallar el índice.
  - Left-Shift: desplaza elementos desde `pos + 1` hasta `tam - 1` una celda a la izquierda.
  - Decremento atómico: `tam--`. Retorna `true` o `false`.

### 3.5. Ordenamiento Burbuja Mejorada con Intercambio de Estructuras (15%)
- **Firma:** `void ordenarBurbuja(T arr[], int tam);`
- **Contrato:**
  - Control de banderas: `huboIntercambio` para terminación anticipada en arreglos ordenados.
  - Permutación: Invocación estricta a `intercambiar(T &a, T &b)` para intercambio completo de dos estructuras pasando ambas por referencia.

### 3.6. Cálculo Estadístico Seguro con Guarda Defensiva (10%)
- **Firma:** `double calcularPromedioAlquiler(const Libro arr[], int tam);` (Tema 1) / `double calcularPromedioPrecioFinal(const Vehiculo arr[], int tam);` (Tema 2)
- **Contrato:**
  - Recorrido secuencial acumulando la métrica clave (importe de alquiler (importeAlquiler) en Tema 1 / precio final (precioFinal) en Tema 2).
  - Guarda defensiva: si `tam <= 0` retorna inmediatamente `0.0` para prevenir división por cero.
  - Retorno de promedio en punto flotante `double` y preservación de solo lectura con calificador `const`.

---

## 4. Matriz de Ponderación Oficial

| Bloque | Contenido | Soporte | Pts |
| :---: | :--- | :---: | :---: |
| 1 | Búsqueda por Clave Primaria (Índice, Centinela -1, Const) | C++ | 10% |
| 2 | Alta / Inserción con Unicidad de Clave (Capacidad, Unicidad, Right-Shift, tam++) | C++ | 15% |
| 3 | Modificación con Clave Inmutable (Reutilización búsqueda, Mutación in-place) | C++ | 10% |
| 4 | Baja Física con Compactación del Arreglo mediante Corrimiento a la Izquierda (Reutilización búsqueda, Left-Shift, tam--) | C++ | 15% |
| 5 | Ordenamiento Burbuja Mejorada con Intercambio de Estructuras (Bandera, Comparación, Intercambio) | C++ | 15% |
| 6 | Cálculo Estadístico Seguro con Guarda Defensiva (Acumulador, tam <= 0, Const) | C++ | 10% |
| 7 | Instancia Escrita: Traza de Ordenamiento (Pasadas, Mín/Aux, Desplazamientos) | Papel | 25% |
| **Total** | **Acreditación Bimodal de Competencias Módulo 4** | **100%** |
