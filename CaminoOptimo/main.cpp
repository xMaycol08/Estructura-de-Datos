/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
 * ALUMNOS:  Maycol Celi
 * FECHA ENTREGA:  06 de enero de 2025
 * PROGRAMA: Busqueda Binaria - Camino Optimo.
 * NRC: 1992
 ***********************************************************************/
#include <iostream>
#include <vector>
#include <limits> // Incluir este encabezado para std::numeric_limits
#include <conio.h> // Incluir este encabezado para _getch()
#include "Validaciones.h"
#include "CaminoOptimo.h"

using namespace std;

int main() {
    try {
        Validaciones val;

        // Obtener dimensiones de la granja
        pair<int, int> dimensiones = val.obtenerDimensiones();
        int n = dimensiones.first;
        int m = dimensiones.second;

        // Crear la matriz de costos
        vector<vector<int>> grid = val.obtenerMatriz(n, m);

        // Calcular el costo mínimo
        CaminoOptimo camino;
        int costoMinimo = camino.calcularCostoMinimo(grid, n, m);

        // Mensaje de salida
        cout << "El costo minimo para llegar a (" << n << ", " << m << ") es: " << costoMinimo << endl;
    } catch (const exception& e) {
        cerr << "Ocurrió un error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Ocurrió un error desconocido." << endl;
        return 1;
    }
    return 0;
}
