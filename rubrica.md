# Rúbrica de Evaluación del Simulacro — 4.º Simulacro de Examen del Módulo 4 (2026)
**Cátedra:** Algoritmos y Programación  
**Módulo 4:** Arreglos de Estructuras (AoS), ABM, Ordenamiento y Estadística  
**Institución:** Universidad Católica de Santiago del Estero — Departamento Académico San Salvador  

---

## 1. Estructura y Modalidad de Evaluación Bimodal

La evaluación se estructura formalmente en dos instancias complementarias que totalizan el 100% de la calificación:

| Instancia | Soporte | Ponderación | Foco Pedagógico |
| :--- | :---: | :---: | :--- |
| **Laboratorio de Programación** | Computadora (C++) | **75%** | Declaración de modelo AoS (tipos primitivos), integración con menú y desarrollo de las 6 funciones lógicas. |
| **Instancia Escrita Individual** | Lápiz y Papel (A4) | **25%** | Traza manual paso a paso de ordenamiento elemental sobre vector numérico ($N=5$). |

---

## 2. Desglose Detallado: Laboratorio de Programación (75% C++)

El código base provisto suministra el esqueleto del programa, el arreglo en RAM con datos precargados y las rutinas de visualización tabular con `<iomanip>`. El estudiante debe declarar los campos del struct según la tabla de dominio, enlazar los `case` del menú interactivo y programar las **6 funciones de lógica algorítmica pura en C++**:

### Bloque 1: Búsqueda por Clave Primaria (10%)
- **Firma Conceptual:** `int buscarPorClave(const T arr[], int tam, int claveBuscada);`
- **Criterios de Evaluación:**
  - **10% (Completo / Excelente):** Recorrido secuencial respetando el tamaño lógico `tam`. Al encontrar la coincidencia, retorna inmediatamente la posición de celda `[0 .. tam-1]`. Esta salida temprana interrumpe inmediatamente el recorrido apenas se localiza la clave, sin recorrer celdas innecesarias. Retorno consistente del valor centinela `-1` si el elemento no existe. Uso de `const` para proteger el arreglo de entrada como parámetro de solo lectura.
  - **5% (Parcial / Básico):** Encuentra el registro pero no retorna `-1` cuando no existe, o no aplica salida temprana recorriendo innecesariamente todo el arreglo.
  - **0% (Insuficiente):** No compila, desborda los límites del arreglo o no localiza el elemento.

### Bloque 2: Alta / Inserción con Unicidad de Clave (15%)
- **Firma Conceptual:**
  ```cpp
  bool insertarRegistro(T arr[], int &tam, int capacidad, int posicion, const T &nuevo);
  ```
- **Parámetros:** Arreglo `arr[]`, tamaño lógico por referencia `&tam`, capacidad física máxima `capacidad`, índice de inserción `posicion` (`0 <= posicion <= tam`) y el registro a insertar `nuevo`.
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Validación rigurosa de límites físicos (`tam < capacidad` y `posicion` dentro de `[0 .. tam]`). **Modularidad de nivel excelente:** Para alcanzar la máxima valoración de modularidad, deberá reutilizar la función de búsqueda previamente implementada. Una búsqueda lineal integrada dentro de la función se considerará funcional, pero recibirá una valoración menor en el criterio de modularidad. Desplazamiento contiguo a la derecha (*Right-Shift: corrimiento de celdas posteriores para abrir espacio*), asignación de `nuevo` en `arr[posicion]` e incremento `tam++`. Retorno de `true` ante éxito o `false` ante rechazo.
  - **10% (Aceptable / Funcional):** Inserta en posición desplazando correctamente y evita duplicados mediante búsqueda in-line (o sin modularizar la llamada), o presenta detalles menores de límites en el corrimiento.
  - **5% (Básico):** Inserta pero no valida unicidad de clave o comete error de límites ("off-by-one") al desplazar.
  - **0% (Insuficiente):** Sobrescribe elementos sin desplazar, no incrementa `tam` o desborda la capacidad física.

### Bloque 3: Modificación con Clave Inmutable (10%)
- **Firma Conceptual:** `bool modificarRegistro(T arr[], int tam, const T &actualizado);`
- **Criterios de Evaluación:**
  - **10% (Completo / Excelente):** Para alcanzar la máxima valoración de modularidad, deberá reutilizar la función de búsqueda previamente implementada. Una búsqueda lineal integrada dentro de la función se considerará funcional, pero recibirá una valoración menor en el criterio de modularidad.
    - **Tema 1 (Libros):** Actualización directa en la celda del año de publicación y precio base, recálculo de antigüedad, categoría e importe de alquiler, y conservación inalterable del código del libro.
    - **Tema 2 (Vehículos):** Reutilización modular recomendada de la búsqueda, modificación in-place exclusivamente de descuentoPorc, preservación de codigo, anioFabricacion, categoria y precioLista, y recálculo correcto de precioFinal.
    - Retorno de `true` si se modificó exitosamente o `false` si el registro no fue encontrado.
  - **6% (Aceptable / Funcional):** Modifica el registro correctamente usando búsqueda in-line sin alterar la clave primaria.
  - **0% (Insuficiente):** Permite modificar la clave primaria, no actualiza el registro o genera inconsistencias en memoria.

### Bloque 4: Baja Física con Compactación del Arreglo mediante Corrimiento a la Izquierda (15%)
- **Firma Conceptual:** `bool darDeBajaFisica(T arr[], int &tam, int claveABorrar);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Para alcanzar la máxima valoración de modularidad, deberá reutilizar la función de búsqueda previamente implementada. Una búsqueda lineal integrada dentro de la función se considerará funcional, pero recibirá una valoración menor en el criterio de modularidad. Desplazamiento contiguo a la izquierda (*Left-Shift: corrimiento de las celdas posteriores hacia adelante para compactar el arreglo sin dejar celdas vacías intermedias*). Decremento del tamaño lógico `tam--`. Retorno de `true` ante éxito o `false` si no existe.
  - **10% (Aceptable / Funcional):** Realiza la baja física compactando correctamente mediante búsqueda in-line.
  - **5% (Básico):** Aplica baja lógica en lugar de física, o comete errores de límites dejando datos residuales al final.
  - **0% (Insuficiente):** Decrementa `tam` sin compactar el arreglo o no reduce el tamaño lógico.

### Bloque 5: Ordenamiento Burbuja Mejorada con Intercambio de Estructuras (15%)
- **Firma Conceptual:** `void ordenarBurbuja(T arr[], int tam);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Algoritmo de **Burbuja Mejorada** con bandera booleana `huboIntercambio` para corte anticipado si el arreglo ya está ordenado. Criterio de comparación estricto por campo clave (precioBase Ascendente en Tema 1 / precioFinal Descendente en Tema 2). **Intercambio de estructuras** *(intercambio de la estructura completa mediante una función auxiliar modular o variable auxiliar de tipo struct, garantizando la integridad de todos sus campos)*.
  - **8% (Aceptable / Funcional):** Implementa Burbuja clásica elemental sin bandera de corte, o con detalles menores en la comparación.
  - **0% (Insuficiente):** No ordena, bucle infinito, permuta campos sueltos en vez del struct completo o utiliza `std::sort`.

### Bloque 6: Cálculo Estadístico Seguro con Guarda Defensiva (10%)
- **Firma Conceptual:** `double calcularPromedio(const T arr[], int tam);`
- **Criterios de Evaluación:**
  - **10% (Completo / Excelente):** Recorrido secuencial acumulando la métrica solicitada (importe de alquiler (importeAlquiler) en Tema 1 / precio final con descuento (precioFinal) en Tema 2). **Guarda defensiva** *(verificación previa `if (tam <= 0) return 0.0;` para prevenir divisiones por cero ante arreglos vacíos)*. División segura en punto flotante retornando `double`. Arreglo recibido con calificador `const`.
  - **5% (Aceptable / Parcial):** Calcula el promedio correctamente pero omite la guarda defensiva o no aplica `const`.
  - **0% (Insuficiente):** No realiza el recorrido, divide por variable errónea o genera error aritmético en tiempo de ejecución.

---

## 3. Desglose Detallado: Instancia Escrita Individual (25% Papel)

Se evalúa la comprensión algorítmica profunda mediante la traza manual paso a paso en hoja de examen A4:

### Tema 1: Selección Directa Ascendente ($V = [35, 12, 68, 24, 7]$)

| Pasada | Rango Subarreglo | Menor Detectado | Swap Realizado | [0] | [1] | [2] | [3] | [4] | Subarreglo Ordenado |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Inicial** | - | - | Ninguno | 35 | 12 | 68 | 24 | 7 | Vacío |
| **i = 0** | [0..4]: {35, 12, 68, 24, 7} | $7$ en índice [4] | $V[0] \leftrightarrow V[4]$ | **7** | 12 | 68 | 24 | 35 | {7} (6.25 pts) |
| **i = 1** | [1..4]: {12, 68, 24, 35} | $12$ en índice [1] | $\text{posMin} == i$ (Sin swap) | **7** | **12** | 68 | 24 | 35 | {7, 12} (6.25 pts) |
| **i = 2** | [2..4]: {68, 24, 35} | $24$ en índice [3] | $V[2] \leftrightarrow V[3]$ | **7** | **12** | **24** | 68 | 35 | {7, 12, 24} (6.25 pts) |
| **i = 3** | [3..4]: {68, 35} | $35$ en índice [4] | $V[3] \leftrightarrow V[4]$ | **7** | **12** | **24** | **35** | **68** | {7, 12, 24, 35, 68} (6.25 pts) |

### Tema 2: Inserción Directa Descendente ($V = [42, 18, 55, 9, 31]$)

| Pasada | Elemento Clave | Comparaciones y Desplazamientos | Inserción en Hueco | [0] | [1] | [2] | [3] | [4] | Subarreglo Ordenado |
| :---: | :---: | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Inicial** | - | Primer elemento ordenado trivialmente | - | 42 | 18 | 55 | 9 | 31 | {42} |
| **i = 1** | $\text{aux} = 18$ | $42 \ge 18$ (No desplaza, 0 corrimientos) | $V[1] = 18$ | **42** | **18** | 55 | 9 | 31 | {42, 18} (6.25 pts) |
| **i = 2** | $\text{aux} = 55$ | $18 < 55$ (desplaza $18$), $42 < 55$ (desplaza $42$) | $V[0] = 55$ | **55** | **42** | **18** | 9 | 31 | {55, 42, 18} (6.25 pts) |
| **i = 3** | $\text{aux} = 9$ | $18 \ge 9$ (No desplaza, 0 corrimientos) | $V[3] = 9$ | **55** | **42** | **18** | **9** | 31 | {55, 42, 18, 9} (6.25 pts) |
| **i = 4** | $\text{aux} = 31$ | $9 < 31$ (desplaza $9$), $18 < 31$ (desplaza $18$), $42 \ge 31$ (frena) | $V[2] = 31$ | **55** | **42** | **31** | **18** | **9** | {55, 42, 31, 18, 9} (6.25 pts) |

---

## 4. Penalizaciones y Criterios Disciplinares

| Falta Técnica | Penalización | Justificación Pedagógica |
| :--- | :---: | :--- |
| **Uso de Vectores Paralelos** | **-50% del examen** | Violación directa de la arquitectura del Módulo 4 (Array of Structs). |
| **Uso de `std::sort` o librerías externas** | **-15% (Bloque 5 anulado)** | Se evalúa la comprensión y codificación del algoritmo de ordenamiento manual. |
| **Errores de Compilación** | **Descuento en bloque (hasta -30%)** | El código entregado debe compilar bajo el estándar C++17. Se descuenta dentro del bloque afectado; si una corrección sintáctica mínima permite evaluar la lógica desarrollada, podrá reconocerse puntaje parcial. |
| **Permutación de campos sueltos en ordenamiento** | **-10%** | Desincroniza los registros destruyendo la integridad de los datos. |

> [!IMPORTANT]
> **Regla de No Acumulación:** Las penalizaciones no se acumularán cuando sancionen el mismo defecto ya considerado en el bloque correspondiente. La calificación final del examen no podrá ser inferior a 0%.

---

## 5. Tabla de Conversión a Nota Final (Escala UCSE 1 a 10)

| Puntaje Total (%) | Nota UCSE | Condición Académica |
| :---: | :---: | :--- |
| **0 – 39%** | **1 – 2** | No Aprobado / Reprobado |
| **40 – 59%** | **3** | Insuficiente (Recupera) |
| **60 – 67%** | **4** | **Aprobado (Mínimo de acreditación)** |
| **68 – 75%** | **5** | Aprobado (Aceptable) |
| **76 – 83%** | **6** | Bueno |
| **84 – 87%** | **7** | Muy Bueno |
| **88 – 91%** | **8** | Distinguido |
| **92 – 95%** | **9** | Excelente |
| **96 – 100%** | **10** | Sobresaliente |
