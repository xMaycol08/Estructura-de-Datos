/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
 * ALUMNOS:  Maycol Celi
 * FECHA ENTREGA:  06 de enero de 2025
 * PROGRAMA: Busqueda Binaria - Problema 2.
 * NRC: 1992
 ***********************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include "BusquedaBinaria.h"
#include "Validaciones.h"

using namespace std;

int main() {
    Validaciones validaciones;
    BusquedaBinaria busquedaBinaria;

    int N, M;
    vector<pair<long long, long long>> intervalos;

    validaciones.leerDatos(N, M, intervalos);
    sort(intervalos.begin(), intervalos.end());

    long long maximaDistancia = busquedaBinaria.encontrarMaximaDistancia(intervalos, N);

    cout << "La mayor distancia posible es: " << maximaDistancia << endl;

    return 0;
}
