#include "Validaciones.h"
#include <iostream>
#include <regex>
#include <limits>
#include <sstream>  // Para la validación de números

// Función para validar que el texto solo contenga letras y espacios
bool validarTexto(const std::string& texto) {
    return std::regex_match(texto, std::regex("[A-Za-z ]+"));
}

// Función para validar el año de publicación (debe estar entre 1800 y 2024)
bool validarAnioPublicacion(int anio) {
    return anio >= 1800 && anio <= 2024;
}

// Función para validar el ISBN (debe contener solo números y guiones)
bool validarISBN(const std::string& isbn) {
    return std::regex_match(isbn, std::regex("[0-9-]+"));
}

// Función para validar el precio (debe ser un número positivo)
bool validarPrecio(double precio) {
    return precio > 0;
}

// Función para validar la calificación (debe estar entre 0 y 5)
bool validarCalificacion(double calificacion) {
    return calificacion >= 0 && calificacion <= 5;
}

// Función para leer y validar números enteros (por ejemplo, año de publicación)
bool ingresarNumero(int& numero) {
    std::string input;
    std::getline(std::cin, input);  // Leer la entrada

    std::stringstream ss(input);
    ss >> numero;

    // Verificar si el número fue leído correctamente y si no quedan caracteres adicionales
    if (ss.fail() || !ss.eof()) {
        return false;  // Si falla o quedan caracteres adicionales, es inválido
    }
    return true;
}

// Función para leer y validar números decimales (por ejemplo, precio o calificación)
bool ingresarNumero(double& numero) {
    std::string input;
    std::getline(std::cin, input);  // Leer la entrada

    std::stringstream ss(input);
    ss >> numero;

    // Verificar si el número fue leído correctamente y si no quedan caracteres adicionales
    if (ss.fail() || !ss.eof()) {
        return false;  // Si falla o quedan caracteres adicionales, es inválido
    }
    return true;
}

// Función para validar que la opción del menú es un número entero
bool ingresarOpcionMenu(int& opcion) {
    std::string input;
    std::getline(std::cin, input);  // Leer la entrada como cadena de texto

    std::stringstream ss(input);
    ss >> opcion;  // Intentar convertir la entrada a un número entero

    // Verificar si el número fue leído correctamente y si no quedan caracteres adicionales
    if (ss.fail() || !ss.eof()) {
        return false;  // Si falla o quedan caracteres adicionales, es inválido
    }

    // Si la conversión es exitosa y no quedan caracteres extra, es válido
    return true;
}
