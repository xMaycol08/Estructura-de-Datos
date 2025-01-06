/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
 * ALUMNOS:  Maycol Celi
 * FECHA ENTREGA:  06 de enero de 2025
 * PROGRAMA: Busqueda Binaria - Problema 1.
 * NRC: 1992
 ***********************************************************************/
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "CityTowerManager.h"
#include "Validaciones.h"

int main() {
    Validations validator;
    int n, m;

    while (true) {
        try {
            std::cout << "Ingrese el numero de ciudades y torres: ";
            std::string input = validator.getValidatedInput();
            std::istringstream iss(input);

            if (!(iss >> n >> m)) {
                throw std::invalid_argument("Formato de entrada invalido");
            }

            if (!validator.validateInput(n, m)) {
                std::cerr << "Entrada invalida!" << std::endl;
                continue;
            }

            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    std::vector<int> cities(n);
    std::vector<int> towers(m);

    while (true) {
        try {
            std::cout << "Ingrese las coordenadas de las ciudades: ";
            std::string input = validator.getValidatedInput();
            std::istringstream iss(input);
            for (int i = 0; i < n; ++i) {
                if (!(iss >> cities[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las coordenadas de las ciudades");
                }
            }
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Ingrese las coordenadas de las torres: ";
            std::string input = validator.getValidatedInput();
            std::istringstream iss(input);
            for (int i = 0; i < m; ++i) {
                if (!(iss >> towers[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las coordenadas de las torres");
                }
            }
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    try {
        CityTowerManager manager(cities, towers);
        int min_r = manager.findMinR();
        std::cout << "La minima distancia r necesaria es: " << min_r << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
