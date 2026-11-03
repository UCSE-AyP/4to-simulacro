#include <iostream>
#include <iomanip>

using namespace std;

struct Vehiculo {
    // Estructura declarada respetando estrictamente el orden del enunciado para inicializacion por llaves
    int codigo;            // Clave Primaria univoca
    int anioFabricacion;   // Anio de fabricacion (<= 2026)
    char categoria;        // 'N' Nuevo (0-1), 'S' Seminuevo (2-5), 'U' Usado (6+)
    double precioLista;    // Precio de lista de concesionaria (> 0)
    double descuentoPorc;  // Descuento comercial aplicado (0..30 %)
    double precioFinal;    // precioLista * (1 - desc/100) * (1 + recargo)
};

// Prototipos de funciones a implementar por el estudiante
void intercambiar(Vehiculo &a, Vehiculo &b);
int buscarPorCodigo(const Vehiculo arr[], int tam, int codigoBuscado);
bool insertarVehiculo(Vehiculo arr[], int &tam, int capacidad, int pos, const Vehiculo &nuevo);
bool modificarVehiculo(Vehiculo arr[], int tam, const Vehiculo &actualizado);
bool darDeBajaVehiculo(Vehiculo arr[], int &tam, int codigoABorrar);
void ordenarPorPrecioBurbujaDesc(Vehiculo arr[], int tam);
double calcularPromedioPrecioFinal(const Vehiculo arr[], int tam);

// Modulos meramente de escritura pre-implementados
void mostrarMenu();
void mostrarFicha(const Vehiculo &e);
void mostrarTabla(const Vehiculo arr[], int tam);

int main() {
    const int CAPACIDAD = 15;
    Vehiculo stock[CAPACIDAD] = {
        {501, 2025, 'N', 25000000.0, 5.0,  26125000.0},
        {622, 2022, 'S', 17500000.0, 10.0, 16537500.0},
        {718, 2017, 'U',  9800000.0, 8.0,   9016000.0},
        {845, 2023, 'S', 21000000.0, 12.0, 19782000.0}
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
                mostrarTabla(stock, tam);
                break;
            case 2: {
                cout << ">>> CONSULTA DE VEHICULO POR CODIGO <<<\n";
                int cod;
                cout << "  Ingrese codigo a buscar: ";
                cin >> cod;
                int pos = buscarPorCodigo(stock, tam, cod);
                if (pos != -1) {
                    cout << "  [OK] Vehiculo localizado en celda [" << pos << "]:\n";
                    mostrarFicha(stock[pos]);
                } else {
                    cout << "  [-] Vehiculo con codigo " << cod << " no existe en el stock.\n";
                }
                break;
            }
            case 3: {
                cout << ">>> ALTA / INSERCION DE VEHICULO EN POSICION <<<\n";
                int pos;
                cout << "  Ingrese posicion donde desea insertar [0 .. " << tam << "]: ";
                cin >> pos;
                Vehiculo nuevo;
                cout << "  Ingrese Codigo del vehiculo (entero unico): ";
                cin >> nuevo.codigo;
                cout << "  Ingrese Anio de fabricacion [1990..2026]: ";
                cin >> nuevo.anioFabricacion;
                cout << "  Ingrese Precio de Lista (> 0): $";
                cin >> nuevo.precioLista;
                cout << "  Ingrese Descuento % (0 a 30): ";
                cin >> nuevo.descuentoPorc;

                int ant = 2026 - nuevo.anioFabricacion;
                if (ant <= 1) nuevo.categoria = 'N';
                else if (ant <= 5) nuevo.categoria = 'S';
                else nuevo.categoria = 'U';

                double rec = (nuevo.categoria == 'N' ? 0.10 : (nuevo.categoria == 'S' ? 0.05 : 0.0));
                nuevo.precioFinal = nuevo.precioLista * (1.0 - nuevo.descuentoPorc / 100.0) * (1.0 + rec);

                if (insertarVehiculo(stock, tam, CAPACIDAD, pos, nuevo)) {
                    cout << "\n  [OK] Vehiculo registrado exitosamente en la celda [" << pos << "]. Total: " << tam << "/" << CAPACIDAD << "\n";
                } else {
                    cout << "\n  [!] ERROR: No se pudo registrar. Verifique codigo duplicado, cupo agotado o posicion invalida.\n";
                }
                break;
            }
            case 4: {
                cout << ">>> MODIFICACION DE DESCUENTO (UPDATE / PK INMUTABLE) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del vehiculo a modificar: ";
                cin >> cod;
                int pos = buscarPorCodigo(stock, tam, cod);
                if (pos == -1) {
                    cout << "\n  [-] Vehiculo no encontrado.\n";
                } else {
                    Vehiculo modificado = stock[pos];
                    cout << "  Modificando unidad con Codigo " << cod << " (inalterable):\n";
                    cout << "  Nuevo Descuento comercial % (0 a 30): ";
                    cin >> modificado.descuentoPorc;

                    double rec = (modificado.categoria == 'N' ? 0.10 : (modificado.categoria == 'S' ? 0.05 : 0.0));
                    modificado.precioFinal = modificado.precioLista * (1.0 - modificado.descuentoPorc / 100.0) * (1.0 + rec);

                    if (modificarVehiculo(stock, tam, modificado)) {
                        cout << "\n  [OK] Descuento y Precio Final modificados exitosamente.\n";
                    } else {
                        cout << "\n  [!] Error al modificar.\n";
                    }
                }
                break;
            }
            case 5: {
                cout << ">>> BAJA FISICA DE VEHICULO (DELETE / COMPACTACION) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del vehiculo a dar de baja: ";
                cin >> cod;
                if (darDeBajaVehiculo(stock, tam, cod)) {
                    cout << "\n  [OK] Registro eliminado y arreglo compactado correctamente. Total activos: " << tam << "\n";
                } else {
                    cout << "\n  [-] Codigo no encontrado. No se realizo ninguna baja.\n";
                }
                break;
            }
            case 6:
                cout << ">>> ORDENAMIENTO BURBUJA (DESCENDENTE POR PRECIO FINAL) <<<\n";
                ordenarPorPrecioBurbujaDesc(stock, tam);
                cout << "  [OK] Stock ordenado de mayor a menor segun precio final con exito.\n";
                mostrarTabla(stock, tam);
                break;
            case 7: {
                cout << ">>> REPORTE ESTADISTICO: CALCULAR PROMEDIO DE PRECIOS FINALES <<<\n";
                double prom = calcularPromedioPrecioFinal(stock, tam);
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

void intercambiar(Vehiculo &a, Vehiculo &b) {
    Vehiculo aux = a;
    a = b;
    b = aux;
}

int buscarPorCodigo(const Vehiculo arr[], int tam, int codigoBuscado) {
    for (int i = 0; i < tam; ++i) {
        if (arr[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

bool insertarVehiculo(Vehiculo arr[], int &tam, int capacidad, int pos, const Vehiculo &nuevo) {
    if (tam >= capacidad || pos < 0 || pos > tam) return false;
    if (buscarPorCodigo(arr, tam, nuevo.codigo) != -1) return false;
    for (int i = tam; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = nuevo;
    tam++;
    return true;
}

bool modificarVehiculo(Vehiculo arr[], int tam, const Vehiculo &actualizado) {
    int pos = buscarPorCodigo(arr, tam, actualizado.codigo);
    if (pos == -1) return false;
    arr[pos].anioFabricacion = actualizado.anioFabricacion;
    arr[pos].categoria = actualizado.categoria;
    arr[pos].precioLista = actualizado.precioLista;
    arr[pos].descuentoPorc = actualizado.descuentoPorc;
    arr[pos].precioFinal = actualizado.precioFinal;
    return true;
}

bool darDeBajaVehiculo(Vehiculo arr[], int &tam, int codigoABorrar) {
    int pos = buscarPorCodigo(arr, tam, codigoABorrar);
    if (pos == -1) return false;
    for (int k = pos; k < tam - 1; ++k) {
        arr[k] = arr[k + 1];
    }
    tam--;
    return true;
}

void ordenarPorPrecioBurbujaDesc(Vehiculo arr[], int tam) {
    bool huboIntercambio = true;
    for (int i = 0; i < tam - 1 && huboIntercambio; ++i) {
        huboIntercambio = false;
        for (int j = 0; j < tam - 1 - i; ++j) {
            if (arr[j].precioFinal < arr[j + 1].precioFinal) {
                intercambiar(arr[j], arr[j + 1]);
                huboIntercambio = true;
            }
        }
    }
}

double calcularPromedioPrecioFinal(const Vehiculo arr[], int tam) {
    if (tam <= 0) return 0.0;
    double suma = 0.0;
    for (int i = 0; i < tam; ++i) {
        suma += arr[i].precioFinal;
    }
    return suma / tam;
}

void mostrarMenu() {
    cout << "\n======================================================================\n";
    cout << "        SISTEMA DE GESTION DE CONCESIONARIA (ARRAY OF STRUCTS)        \n";
    cout << "======================================================================\n";
    cout << "  1. Listar Stock de Vehiculos (Formato Tabular)\n";
    cout << "  2. Consultar Vehiculo por Codigo (Read)\n";
    cout << "  3. Registrar Nuevo Vehiculo en Posicion (Create / Right-Shift)\n";
    cout << "  4. Modificar Vehiculo Existente (Update / PK Inmutable)\n";
    cout << "  5. Dar de Baja Fisica de Vehiculo (Delete / Left-Shift)\n";
    cout << "  6. Ordenar por Precio Final (Burbuja Descendente)\n";
    cout << "  7. Calcular Promedio de Precios Finales (Estadistica / Const)\n";
    cout << "  0. Salir\n";
    cout << "======================================================================\n";
}

void mostrarFicha(const Vehiculo &e) {
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | FICHA TECNICA DE UNIDAD AUTOMOTOR                                |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | Codigo Vehiculo:  " << left << setw(47) << e.codigo << "|\n";
    cout << "  | Anio Fabricacion: " << left << setw(47) << e.anioFabricacion << "|\n";
    cout << "  | Categoria:        " << left << setw(47) << (e.categoria == 'N' ? "N (Nuevo 0-1)" : (e.categoria == 'S' ? "S (Seminuevo 2-5)" : "U (Usado 6+)")) << "|\n";
    cout << "  | Precio de Lista: $" << left << setw(46) << fixed << setprecision(2) << e.precioLista << "|\n";
    cout << "  | Descuento:        " << left << setw(45) << fixed << setprecision(1) << e.descuentoPorc << "%|\n";
    cout << "  | Precio Final:    $" << left << setw(46) << fixed << setprecision(2) << e.precioFinal << "|\n";
    cout << "  +------------------------------------------------------------------+\n" << right;
}

void mostrarTabla(const Vehiculo arr[], int tam) {
    if (tam == 0) {
        cout << "  [!] El stock automotor esta vacio (tam = 0).\n";
        return;
    }

    cout << "\n+-----+--------+----------+-----+---------------+--------+---------------+\n";
    cout << "| POS | CODIGO | ANIO FAB | CAT | PREC. LISTA   | DESC % | PRECIO FINAL  |\n";
    cout << "+-----+--------+----------+-----+---------------+--------+---------------+\n";

    cout << right;
    for (int i = 0; i < tam; ++i) {
        cout << "| [" << setw(1) << i << "] | "
             << setw(6) << arr[i].codigo << " |   "
             << setw(6) << arr[i].anioFabricacion << " |  "
             << arr[i].categoria << "  | $"
             << setw(12) << fixed << setprecision(2) << arr[i].precioLista << " |  "
             << setw(4) << fixed << setprecision(1) << arr[i].descuentoPorc << "% | $"
             << setw(12) << fixed << setprecision(2) << arr[i].precioFinal << " |\n";
    }
    cout << "+-----+--------+----------+-----+---------------+--------+---------------+\n";
    cout << "Total vehiculos en stock: " << tam << ".\n";
}
