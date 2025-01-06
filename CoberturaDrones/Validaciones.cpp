#include "Validaciones.h"
#include <iostream>
#include <conio.h>
#include <sstream>
#include <stdexcept>

// Validar los valores de entrada
bool Validaciones::validarEntradas(int n, int m, const std::vector<int>& areas, const std::vector<int>& drones) {
    try {
        if (n < 2 || n > 100000) {
            throw std::out_of_range("El numero de areas de vigilancia debe estar entre 2 y 100000.");
        }
        if (m < 1 || m > 100000) {
            throw std::out_of_range("El numero de drones debe estar entre 1 y 100000.");
        }
        if (areas.size() != n) {
            throw std::invalid_argument("El tamano de la lista de areas no coincide con el valor proporcionado.");
        }
        if (drones.size() != m) {
            throw std::invalid_argument("El tamano de la lista de drones no coincide con el valor proporcionado.");
        }
        for (int i = 1; i < n; ++i) {
            if (areas[i] <= areas[i - 1]) {
                throw std::logic_error("Las posiciones de las areas de vigilancia no estan ordenadas correctamente.");
            }
        }
        for (int i = 1; i < m; ++i) {
            if (drones[i] <= drones[i - 1]) {
                throw std::logic_error("Las posiciones de los drones no estan ordenadas correctamente.");
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

// Mostrar mensaje de entrada
void Validaciones::mensajeEntrada(const std::string& tipo) {
    std::cout << "Ingrese las " << tipo << ": ";
}

// Mostrar mensaje de salida
void Validaciones::mensajeSalida(int radioMinimo) {
    std::cout << "El radio minimo requerido es: " << radioMinimo << std::endl;
}

// Validar y filtrar caracteres de entrada
void Validaciones::filtrarEntrada(std::string& input, int maxNumeros) {
    char c;
    int count = 0;
    int numCount = 0;
    bool lastWasDigit = false;
    bool lastWasDash = false;
    while ((c = _getch()) != '\r') { // Leer hasta Enter
        if ((c >= '0' && c <= '9') || c == ' ' || (c == '-' && !lastWasDigit && !lastWasDash && (input.empty() || input.back() == ' '))) {
            if (c == ' ') {
                numCount++;
                if (numCount >= maxNumeros) {
                    std::cerr << "\nPor favor, ingrese exactamente " << maxNumeros << " numeros." << std::endl;
                    input.clear();
                    numCount = 0;
                    std::cout << "Ingrese los numeros nuevamente: ";
                    continue;
                }
            }
            std::cout << c;
            input += c;
            lastWasDigit = (c >= '0' && c <= '9');
            lastWasDash = (c == '-');
        } else if (c == '-' && lastWasDigit) { // Ensure '-' is not allowed after a digit
            continue;
        } else if (c == '\b' && !input.empty()) { // Manejar backspace
            std::cout << "\b \b";
            if (input.back() == ' ') {
                numCount--;
            }
            lastWasDigit = (input.back() >= '0' && input.back() <= '9');
            lastWasDash = (input.back() == '-');
            input.pop_back();
        }
    }
    std::cout << std::endl;
    numCount++; // Count the last number
    if (numCount != maxNumeros) {
        throw std::invalid_argument("Numero incorrecto de entradas proporcionadas.");
    }
}

// Validar que se ingresen exactamente dos números
bool Validaciones::validarDosNumeros(const std::string& input, int& n, int& m) {
    std::stringstream ss(input);
    ss >> n >> m;
    if (!ss.fail() && ss.eof() && n >= 2 && n <= 100000 && m >= 1 && m <= 100000) {
        return true;
    }
    return false;
}
