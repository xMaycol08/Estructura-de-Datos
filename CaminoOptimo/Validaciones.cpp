#include "Validaciones.h"
#include <iostream>
#include <regex>
#include <conio.h> // Incluir este encabezado para _getch()
#include <sstream>

bool Validaciones::validarDimensiones(int n, int m) {
    try {
        std::cout << "Validando dimensiones: " << n << "x" << m << std::endl;
        bool valid = (n >= 1 && n <= 1000) && (m >= 1 && m <= 1000);
        if (valid) {
            std::cout << "Dimensiones validas." << std::endl;
        } else {
            std::cout << "Dimensiones invalidas." << std::endl;
        }
        return valid;
    } catch (const std::exception& e) {
        std::cerr << "Error validando dimensiones: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Error desconocido validando dimensiones." << std::endl;
        return false;
    }
}

bool Validaciones::esEntradaValida(const std::string& entrada) {
    // Expresion regular para validar que la entrada solo contiene numeros, espacios y el signo menos
    std::regex patron("^-?\\d+(\\s+-?\\d+)*$");
    return std::regex_match(entrada, patron);
}

bool Validaciones::esCaracterValido(char c, const std::string& entrada) {
    if (c == '-') {
        // El signo menos solo es valido si es el primer caracter o si sigue a un espacio
        return entrada.empty() || entrada.back() == ' ';
    }
    return (isdigit(c) || c == '\b' || c == '\r' || c == ' ');
}

std::string Validaciones::obtenerEntrada() {
    std::string entrada;
    char c;
    while ((c = _getch()) != '\r') { // Leer hasta que se presione Enter
        if (esCaracterValido(c, entrada)) {
            if (c == '\b') { // Manejar retroceso
                if (!entrada.empty()) {
                    std::cout << "\b \b";
                    entrada.pop_back();
                }
            } else {
                std::cout << c;
                entrada.push_back(c);
            }
        }
    }
    std::cout << std::endl;
    return entrada;
}

std::vector<std::vector<int>> Validaciones::obtenerMatriz(int n, int m) {
    std::vector<std::vector<int>> matriz(n, std::vector<int>(m));
    std::cout << "Ingrese los costos de las celdas:" << std::endl;
    for (int i = 0; i < n; ++i) {
        while (true) {
            std::string entrada = obtenerEntrada();
            std::istringstream iss(entrada);
            std::vector<int> fila;
            int num;
            while (iss >> num) {
                fila.push_back(num);
            }
            if (fila.size() == m) {
                matriz[i] = fila;
                break;
            } else {
                std::cout << "Entrada invalida. Asegurese de ingresar exactamente " << m << " numeros. Intente nuevamente:\n";
                i = -1; // Reiniciar la entrada de la matriz
                break;
            }
        }
    }
    return matriz;
}

std::pair<int, int> Validaciones::obtenerDimensiones() {
    int n, m;
    while (true) {
        std::cout << "Ingrese las dimensiones de la granja (n m): ";
        std::string dimensiones = obtenerEntrada();
        std::istringstream iss(dimensiones);
        std::vector<int> dim;
        int num;
        while (iss >> num) {
            dim.push_back(num);
        }
        if (dim.size() == 2 && esEntradaValida(dimensiones)) {
            n = dim[0];
            m = dim[1];
            if (validarDimensiones(n, m)) {
                break;
            } else {
                std::cout << "Dimensiones invalidas. Por favor, intente nuevamente." << std::endl;
            }
        } else {
            std::cout << "Entrada invalida. Asegurese de ingresar solo dos numeros enteros. Intente nuevamente." << std::endl;
        }
    }
    return {n, m};
}
