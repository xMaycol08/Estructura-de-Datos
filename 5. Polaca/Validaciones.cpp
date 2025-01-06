#include "Validaciones.h"
#include <iostream>
#include <conio.h> // for getch()

bool esCaracterValido(char c) {
    return isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

int obtenerOpcion() {
    try {
        int opcion = 0;
        char c;
        while (true) {
            c = _getch();
            if (isdigit(c)) {
                opcion = c - '0';
                std::cout << c << std::endl;
                break;
            } else if (c == '\r') { // Enter key
                std::cout << std::endl;
                return -1;
            }
        }
        return opcion;
    } catch (const exception &e) {
        std::cerr << "Error al obtener la opcion: " << e.what() << std::endl;
        return -1;
    }
}

std::string obtenerExpresion() {
    try {
        std::string expresion;
        char c;
        while ((c = _getch()) != '\r') { // '\r' is the Enter key
            if (c == '\b') { // Backspace key
                if (!expresion.empty()) {
                    expresion.pop_back();
                    std::cout << "\b \b"; // Erase the last character from the console
                }
            } else if (esCaracterValido(c)) {
                expresion += c;
                std::cout << c;
            }
        }
        std::cout << std::endl;
        return expresion;
    } catch (const exception &e) {
        std::cerr << "Error al obtener la expresion: " << e.what() << std::endl;
        return "";
    }
}
