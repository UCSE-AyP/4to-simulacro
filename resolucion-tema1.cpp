#include <iostream>
#include <iomanip>

using namespace std;

struct Libro {
    // Estructura declarada respetando estrictamente el orden del enunciado para inicializacion por llaves
    int codigo;            // Clave Primaria univoca
    int anioPub;           // Anio de publicacion (<= 2026)
    int antiguedad;        // 2026 - anioPub
    char categoria;        // 'N' (Nuevo <=5), 'R' (Regular 6..20), 'A' (Antiguo >20)
    double precioBase;     // Tarifa base diaria (> 0)
    double importeAlquiler;// precioBase + % segun categoria (N:+20%, R:+15%, A:+10%)
};

// Prototipos de funciones a implementar por el estudiante
void intercambiar(Libro &a, Libro &b);
int buscarPorCodigo(const Libro arr[], int tam, int codigoBuscado);
bool insertarLibro(Libro arr[], int &tam, int capacidad, int pos, const Libro &nuevo);
bool modificarLibro(Libro arr[], int tam, const Libro &actualizado);
bool darDeBajaLibro(Libro arr[], int &tam, int codigoABorrar);
void ordenarPorPrecioBaseBurbujaAsc(Libro arr[], int tam);
double calcularPromedioAlquiler(const Libro arr[], int tam);

// Modulos meramente de escritura pre-implementados
void mostrarMenu();
void mostrarFicha(const Libro &e);
void mostrarTabla(const Libro arr[], int tam);

int main() {
    const int CAPACIDAD = 15;
    Libro catalogo[CAPACIDAD] = {
        {1001, 2022, 4,  'N', 4500.0, 5400.0},
        {1040, 2016, 10, 'R', 3800.0, 4370.0},
        {1205, 2003, 23, 'A', 5200.0, 5720.0},
        {1310, 2025, 1,  'N', 6100.0, 7320.0}
    };
    int tam = 4;

    int opcion = 0;
    do {
        mostrarMenu();
        cout << "  Seleccione una opcion [1-7, 0 para salir]: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cout << "\n----------------------------------------------------------------------\n";
        switch (opcion) {
            case 1:
                mostrarTabla(catalogo, tam);
                break;
            case 2: {
                cout << ">>> CONSULTA DE LIBRO POR CODIGO <<<\n";
                int cod;
                cout << "  Ingrese codigo a buscar: ";
                cin >> cod;
                int pos = buscarPorCodigo(catalogo, tam, cod);
                if (pos != -1) {
                    cout << "  [OK] Libro localizado en celda [" << pos << "]:\n";
                    mostrarFicha(catalogo[pos]);
                } else {
                    cout << "  [-] Libro con codigo " << cod << " no existe en el catalogo.\n";
                }
                break;
            }
            case 3: {
                cout << ">>> ALTA / INSERCION DE LIBRO EN POSICION <<<\n";
                int pos;
                cout << "  Ingrese posicion donde desea insertar [0 .. " << tam << "]: ";
                cin >> pos;
                Libro nuevo;
                cout << "  Ingrese Codigo del libro (entero unico): ";
                cin >> nuevo.codigo;
                cout << "  Ingrese Anio de publicacion [1500..2026]: ";
                cin >> nuevo.anioPub;
                cout << "  Ingrese Precio Base de Alquiler (> 0): $";
                cin >> nuevo.precioBase;

                nuevo.antiguedad = 2026 - nuevo.anioPub;
                if (nuevo.antiguedad <= 5) nuevo.categoria = 'N';
                else if (nuevo.antiguedad <= 20) nuevo.categoria = 'R';
                else nuevo.categoria = 'A';

                double rec = (nuevo.categoria == 'N' ? 0.20 : (nuevo.categoria == 'R' ? 0.15 : 0.10));
                nuevo.importeAlquiler = nuevo.precioBase * (1.0 + rec);

                if (insertarLibro(catalogo, tam, CAPACIDAD, pos, nuevo)) {
                    cout << "\n  [OK] Libro registrado exitosamente en la celda [" << pos << "]. Total: " << tam << "/" << CAPACIDAD << "\n";
                } else {
                    cout << "\n  [!] ERROR: No se pudo registrar. Verifique codigo duplicado, cupo agotado o posicion invalida.\n";
                }
                break;
            }
            case 4: {
                cout << ">>> MODIFICACION DE LIBRO (UPDATE / PK INMUTABLE) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del libro a modificar: ";
                cin >> cod;
                int pos = buscarPorCodigo(catalogo, tam, cod);
                if (pos == -1) {
                    cout << "\n  [-] Libro no encontrado.\n";
                } else {
                    Libro modificado;
                    modificado.codigo = cod; // Clave primaria inmutable
                    cout << "  Modificando libro con Codigo: " << cod << " (inalterable)\n";
                    cout << "  Nuevo Anio de publicacion [1500..2026]: ";
                    cin >> modificado.anioPub;
                    cout << "  Nuevo Precio Base de Alquiler (> 0): $";
                    cin >> modificado.precioBase;

                    modificado.antiguedad = 2026 - modificado.anioPub;
                    if (modificado.antiguedad <= 5) modificado.categoria = 'N';
                    else if (modificado.antiguedad <= 20) modificado.categoria = 'R';
                    else modificado.categoria = 'A';

                    double rec = (modificado.categoria == 'N' ? 0.20 : (modificado.categoria == 'R' ? 0.15 : 0.10));
                    modificado.importeAlquiler = modificado.precioBase * (1.0 + rec);

                    if (modificarLibro(catalogo, tam, modificado)) {
                        cout << "\n  [OK] Libro modificado exitosamente.\n";
                    } else {
                        cout << "\n  [!] Error al modificar.\n";
                    }
                }
                break;
            }
            case 5: {
                cout << ">>> BAJA FISICA DE LIBRO (DELETE / COMPACTACION) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del libro a dar de baja: ";
                cin >> cod;
                if (darDeBajaLibro(catalogo, tam, cod)) {
                    cout << "\n  [OK] Registro eliminado y arreglo compactado correctamente. Total activos: " << tam << "\n";
                } else {
                    cout << "\n  [-] Codigo no encontrado. No se realizo ninguna baja.\n";
                }
                break;
            }
            case 6:
                cout << ">>> ORDENAMIENTO BURBUJA (ASCENDENTE POR PRECIO BASE) <<<\n";
                ordenarPorPrecioBaseBurbujaAsc(catalogo, tam);
                cout << "  [OK] Catalogo ordenado de menor a mayor segun precio base con exito.\n";
                mostrarTabla(catalogo, tam);
                break;
            case 7: {
                cout << ">>> REPORTE ESTADISTICO: CALCULAR PROMEDIO DE IMPORTE DE ALQUILER <<<\n";
                double prom = calcularPromedioAlquiler(catalogo, tam);
                cout << "  [RESULTADO] Promedio calculado: $" << fixed << setprecision(2) << prom << "\n";
                break;
            }
            case 0:
                cout << "  [SISTEMA]: Sesion finalizada. Fin del programa.\n";
                break;
            default:
                cout << "  [!] Opcion no valida. Seleccione una opcion valida del menu [0 a 6].\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}

void intercambiar(Libro &a, Libro &b) {
    Libro aux = a;
    a = b;
    b = aux;
}

int buscarPorCodigo(const Libro arr[], int tam, int codigoBuscado) {
    for (int i = 0; i < tam; ++i) {
        if (arr[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

bool insertarLibro(Libro arr[], int &tam, int capacidad, int pos, const Libro &nuevo) {
    if (tam >= capacidad || pos < 0 || pos > tam) return false;
    if (buscarPorCodigo(arr, tam, nuevo.codigo) != -1) return false;
    for (int i = tam; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = nuevo;
    tam++;
    return true;
}

bool modificarLibro(Libro arr[], int tam, const Libro &actualizado) {
    int pos = buscarPorCodigo(arr, tam, actualizado.codigo);
    if (pos == -1) return false;
    arr[pos].anioPub = actualizado.anioPub;
    arr[pos].antiguedad = actualizado.antiguedad;
    arr[pos].categoria = actualizado.categoria;
    arr[pos].precioBase = actualizado.precioBase;
    arr[pos].importeAlquiler = actualizado.importeAlquiler;
    return true;
}

bool darDeBajaLibro(Libro arr[], int &tam, int codigoABorrar) {
    int pos = buscarPorCodigo(arr, tam, codigoABorrar);
    if (pos == -1) return false;
    for (int k = pos; k < tam - 1; ++k) {
        arr[k] = arr[k + 1];
    }
    tam--;
    return true;
}

void ordenarPorPrecioBaseBurbujaAsc(Libro arr[], int tam) {
    bool huboIntercambio = true;
    for (int i = 0; i < tam - 1 && huboIntercambio; ++i) {
        huboIntercambio = false;
        for (int j = 0; j < tam - 1 - i; ++j) {
            if (arr[j].precioBase > arr[j + 1].precioBase) {
                intercambiar(arr[j], arr[j + 1]);
                huboIntercambio = true;
            }
        }
    }
}

double calcularPromedioAlquiler(const Libro arr[], int tam) {
    if (tam <= 0) return 0.0;
    double suma = 0.0;
    for (int i = 0; i < tam; ++i) {
        suma += arr[i].importeAlquiler;
    }
    return suma / tam;
}

void mostrarMenu() {
    cout << "\n======================================================================\n";
    cout << "        SISTEMA DE GESTION DE BIBLIOTECA (ARRAY OF STRUCTS)           \n";
    cout << "======================================================================\n";
    cout << "  1. Listar Catalogo de Libros (Formato Tabular)\n";
    cout << "  2. Consultar Libro por Codigo (Read)\n";
    cout << "  3. Registrar Nuevo Libro en Posicion (Create / Right-Shift)\n";
    cout << "  4. Modificar Libro Existente (Update / PK Inmutable)\n";
    cout << "  5. Dar de Baja Fisica de Libro (Delete / Left-Shift)\n";
    cout << "  6. Ordenar por Precio Base (Burbuja Ascendente)\n";
    cout << "  7. Calcular Promedio de Importe de Alquiler (Estadistica / Const)\n";
    cout << "  0. Salir\n";
    cout << "======================================================================\n";
}

void mostrarFicha(const Libro &e) {
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | FICHA TECNICA DE LIBRO REGISTRADO                                |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | Codigo Libro:     " << left << setw(47) << e.codigo << "|\n";
    cout << "  | Anio Publicacion: " << left << setw(47) << e.anioPub << "|\n";
    cout << "  | Antiguedad:       " << left << setw(45) << e.antiguedad << " anios|\n";
    cout << "  | Categoria:        " << left << setw(47) << (e.categoria == 'N' ? "N (Nuevo <= 5)" : (e.categoria == 'R' ? "R (Regular 6..20)" : "A (Antiguo > 20)")) << "|\n";
    cout << "  | Precio Base:     $" << left << setw(46) << fixed << setprecision(2) << e.precioBase << "|\n";
    cout << "  | Importe Alquiler:$" << left << setw(46) << fixed << setprecision(2) << e.importeAlquiler << "|\n";
    cout << "  +------------------------------------------------------------------+\n" << right;
}

void mostrarTabla(const Libro arr[], int tam) {
    if (tam == 0) {
        cout << "  [!] El catalogo esta vacio (tam = 0).\n";
        return;
    }

    cout << "\n+-----+--------+----------+------+-----+-------------+----------------+\n";
    cout << "| POS | CODIGO | ANIO PUB | ANT. | CAT | PRECIO BASE | IMP. ALQUILER  |\n";
    cout << "+-----+--------+----------+------+-----+-------------+----------------+\n";

    cout << right;
    for (int i = 0; i < tam; ++i) {
        cout << "| [" << setw(1) << i << "] | "
             << setw(6) << arr[i].codigo << " |   "
             << setw(6) << arr[i].anioPub << " |  "
             << setw(3) << arr[i].antiguedad << " |  "
             << arr[i].categoria << "  | $"
             << setw(10) << fixed << setprecision(2) << arr[i].precioBase << " | $"
             << setw(13) << fixed << setprecision(2) << arr[i].importeAlquiler << " |\n";
    }
    cout << "+-----+--------+----------+------+-----+-------------+----------------+\n";
    cout << "Total libros en catalogo: " << tam << ".\n";
}
