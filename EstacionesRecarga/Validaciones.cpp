#include "Validaciones.h"
#include <iostream>
#include <sstream>
#include <limits> // Incluir limites
#include <conio.h> // Incluir conio para _getch()

// Función para leer una línea filtrando caracteres no permitidos
std::string leerLineaFiltrada() {
    std::string linea;
    char ch;
    while ((ch = _getch()) != '\r') { // Leer hasta Enter (carácter de retorno de carro)
        if ((ch >= '0' && ch <= '9') || ch == ' ' || ch == '\b') { // Permitir números, espacio y borrar
            if (ch == '\b') { // Manejar borrar
                if (!linea.empty()) {
                    std::cout << "\b \b"; // Borrar el último carácter en la consola
                    linea.pop_back();
                }
            } else {
                std::cout << ch; // Mostrar el carácter permitido
                linea += ch;
            }
        }
    }
    std::cout << std::endl; // Nueva línea después de Enter
    return linea;
}

// Metodo para validar la entrada
bool Validaciones::validarEntrada(int& N, int& M, std::vector<std::pair<int, int>>& intervalos) {
    if (!leerYValidarNM(N, M)) {
        mostrarMensajeError(1);
        return false;
    }
    if (!leerYValidarIntervalos(M, intervalos)) {
        return false;
    }
    return true;
}

// Metodo para mostrar mensajes de error
void Validaciones::mostrarMensajeError(int codigoError) {
    switch (codigoError) {
        case 1:
            std::cerr << "Error: N debe estar entre 2 y 100000, y M debe estar entre 1 y 100000, y solo deben ser dos numeros." << std::endl;
            break;
        case 2:
            std::cerr << "Error: Cada intervalo debe cumplir con 0 <= a <= b y solo deben ser dos numeros." << std::endl;
            break;
        default:
            std::cerr << "Error desconocido." << std::endl;
            break;
    }
}

// Metodo para leer y validar N y M
bool Validaciones::leerYValidarNM(int& N, int& M) {
    while (true) {
        std::cout << "Ingrese el numero de estaciones (N) y el numero de intervalos (M): ";
        std::string linea = leerLineaFiltrada();
        std::istringstream iss(linea);
        int tempN, tempM;
        if (!(iss >> tempN >> tempM) || !(iss >> std::ws).eof() || tempN < 2 || tempM < 1 || tempM > 100000) {
            mostrarMensajeError(1);
        } else {
            N = tempN;
            M = tempM;
            break; // Salir del bucle si N y M son validos
        }
    }
    return true;
}

// Metodo para leer y validar intervalos
bool Validaciones::leerYValidarIntervalos(int M, std::vector<std::pair<int, int>>& intervalos) {
    intervalos.resize(M);
    for (int i = 0; i < M; ++i) {
        while (true) {
            std::cout << "Ingrese el intervalo " << i + 1 << " (a b): ";
            std::string linea = leerLineaFiltrada();
            std::istringstream iss(linea);
            int a, b;
            if (!(iss >> a >> b) || !(iss >> std::ws).eof() || a < 0 || a > b) {
                mostrarMensajeError(2);
            } else {
                intervalos[i] = {a, b};
                break; // Salir del bucle si el intervalo es valido
            }
        }
    }
    return true;
}
