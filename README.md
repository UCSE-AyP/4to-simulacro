# 🚀 4to Examen Simulacro 2026 — Módulo 4: Arreglos de Estructuras (AoS)

**Universidad Católica de Santiago del Estero — Departamento Académico San Salvador**  
**Facultad de Ciencias de la Salud y Tecnologías de la Información**  
**Cátedra:** Algoritmos y Programación  
**Ciclo Lectivo:** 2026  

---

## 🌐 Portal Web Interactivo (GitHub Pages)

Puede acceder directamente al entorno web del simulacro alojado en GitHub Pages:  
👉 **[https://ucse-ayp.github.io/4to-simulacro-2026/](https://ucse-ayp.github.io/4to-simulacro-2026/)**

---

## 📋 Estructura y Contenidos del Repositorio

El presente simulacro evalúa competencias bimodales en C++17 (75% Laboratorio de Programación) e Instancia Escrita manuscrita (25% Lápiz y Papel sobre hoja A4):

### 🖥️ Entorno Interactivo Web
| Archivo | Descripción | Enlace Web |
| :--- | :--- | :---: |
| **`index.html`** | Portal institucional de acceso para alumnos | [Ver Portal](https://ucse-ayp.github.io/4to-simulacro-2026/) |
| **`tema1.html`** | Enunciado interactivo — **Tema 1: Sistema de Alquiler de Libros (AoS)** | [Ver Tema 1](https://ucse-ayp.github.io/4to-simulacro-2026/tema1.html) |
| **`tema2.html`** | Enunciado interactivo — **Tema 2: Concesionaria de Vehículos (AoS)** | [Ver Tema 2](https://ucse-ayp.github.io/4to-simulacro-2026/tema2.html) |
| **`admin.html`** | Panel docente centralizado con accesos a especificaciones y matrices | [Ver Panel](https://ucse-ayp.github.io/4to-simulacro-2026/admin.html) |
| **`prueba_escritorio_imprimir.html`** | Hoja A4 lista para impresión con grillas de traza manuscrita | [Ver Hoja A4](https://ucse-ayp.github.io/4to-simulacro-2026/prueba_escritorio_imprimir.html) |
| **`prueba_escritorio_resuelto.html`** | Solución paso a paso de las trazas de ordenamiento elemental | [Ver Solución](https://ucse-ayp.github.io/4to-simulacro-2026/prueba_escritorio_resuelto.html) |

---

### 💻 Resoluciones de Referencia en C++
- **`resolucion-tema1.cpp`:** Implementación completa y modular del Tema 1 (Libros: Búsqueda, Inserción con corrimiento, Modificación in-place, Baja física con compactación, Ordenamiento Burbuja Mejorada Ascendente por `precioBase`, Promedio con guarda defensiva y funciones de visualización tabular `<iomanip>`).
- **`resolucion-tema2.cpp`:** Implementación completa y modular del Tema 2 (Vehículos: Búsqueda, Inserción con corrimiento, Modificación in-place, Baja física con compactación, Ordenamiento Burbuja Mejorada Descendente por `precioFinal`, Promedio con guarda defensiva y funciones de visualización tabular `<iomanip>`).

#### Compilación y Ejecución (Estándar C++17)
```bash
# Tema 1
g++ -std=c++17 -Wall -Wextra resolucion-tema1.cpp -o tema1.exe
./tema1.exe

# Tema 2
g++ -std=c++17 -Wall -Wextra resolucion-tema2.cpp -o tema2.exe
./tema2.exe
```

---

### 📑 Documentación Pedagógica y de Diseño
- **`SDD.md` (Software Design Document):** Especificación formal de arquitectura, modelos de structs (`100% tipos primitivos`), contratos de precondición/postcondición y matrices de prueba.
- **`rubrica.md`:** Rúbrica analítica oficial de corrección para el equipo docente (ponderación 75% C++ / 25% Escrita).
- **`rubrica_estudiantes.md`:** Criterios de evaluación y escalas de acreditación en lenguaje transparente para estudiantes.

