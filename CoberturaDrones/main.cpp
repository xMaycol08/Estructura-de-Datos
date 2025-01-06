#include <iostream>
#include <vector>
#include <sstream> // Incluir la cabecera para std::stringstream
#include "Validaciones.h"
#include "Cobertura.h"

int main() {
    try {
        Validaciones validaciones;
        int n, m;

        // Leer el número de áreas de vigilancia y drones
        std::string input;
        do {
            std::cout << "Ingrese el numero de areas de vigilancia y drones: ";
            input.clear();
            validaciones.filtrarEntrada(input, 2);
            if (!validaciones.validarDosNumeros(input, n, m)) {
                std::cerr << "Por favor, ingrese exactamente dos numeros en el rango permitido (2 <= N <= 100000, 1 <= M <= 100000)." << std::endl;
            }
        } while (!validaciones.validarDosNumeros(input, n, m));

        std::vector<int> areas(n);
        std::vector<int> drones(m);

        while (true) {
            try {
                // Leer las posiciones de las áreas de vigilancia
                validaciones.mensajeEntrada("posiciones de las areas de vigilancia");
                input.clear();
                validaciones.filtrarEntrada(input, n);
                std::stringstream ssAreas(input);
                for (int i = 0; i < n; ++i) {
                    ssAreas >> areas[i];
                }

                // Verificar que las posiciones de las áreas estén en orden ascendente
                for (int i = 1; i < n; ++i) {
                    if (areas[i] <= areas[i - 1]) {
                        throw std::runtime_error("Las posiciones de las areas de vigilancia no estan ordenadas correctamente.");
                    }
                }

                break; // Salir del bucle si todo es válido
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cerr << "Por favor, intente de nuevo." << std::endl;
            }
        }

        while (true) {
            try {
                // Leer las posiciones iniciales de los drones
                validaciones.mensajeEntrada("posiciones iniciales de los drones");
                input.clear();
                validaciones.filtrarEntrada(input, m);
                std::stringstream ssDrones(input);
                for (int i = 0; i < m; ++i) {
                    ssDrones >> drones[i];
                }

                // Verificar que las posiciones de los drones estén en orden ascendente
                for (int i = 1; i < m; ++i) {
                    if (drones[i] <= drones[i - 1]) {
                        throw std::runtime_error("Las posiciones de los drones no estan ordenadas correctamente.");
                    }
                }

                // Validar las entradas
                if (!validaciones.validarEntradas(n, m, areas, drones)) {
                    throw std::runtime_error("Entradas no validas");
                }

                // Calcular el radio mínimo
                Cobertura cobertura;
                int radioMinimo = cobertura.calcularRadioMinimo(n, m, areas, drones);
                validaciones.mensajeSalida(radioMinimo);
                break; // Salir del bucle si todo es válido
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cerr << "Por favor, intente de nuevo." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
