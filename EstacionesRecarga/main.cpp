/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
 * ALUMNOS:  Maycol Celi
 * FECHA ENTREGA:  06 de enero de 2025
 * PROGRAMA: Busqueda Binaria - Estaciones Recarga.
 * NRC: 1992
 ***********************************************************************/
#include <iostream>
#include <vector>
#include "Estaciones.h"
#include "Validaciones.h"

int main() {
    int N, M;
    std::vector<std::pair<int, int>> intervalos;
    Validaciones validaciones;

    while (true) {
        try {
            if (!validaciones.validarEntrada(N, M, intervalos)) {
                continue; // Solicitar nueva entrada
            }

            Estaciones estaciones(N, intervalos);
            // Calcular la distancia maxima
            int distanciaMaxima = estaciones.calcularDistanciaMaxima();
            
            // Formato de salida:
            // Un numero entero que representa la mayor distancia minima posible.
            std::cout << "La mayor distancia minima posible es: " << distanciaMaxima << std::endl;
            break; // Salir del bucle si todo es valido
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Por favor, intente de nuevo." << std::endl;
        }
    }
    return 0;
}
