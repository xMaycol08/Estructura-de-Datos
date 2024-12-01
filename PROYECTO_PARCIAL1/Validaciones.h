#pragma once
#include <string>

// Funciones de validación
bool validarTexto(const std::string& texto);        // Valida que solo contenga letras y espacios
bool validarAnioPublicacion(int anio);              // Valida que el año esté entre 1800 y 2024
bool validarISBN(const std::string& isbn);          // Valida que el ISBN contenga solo números y guiones
bool validarPrecio(double precio);                  // Valida que el precio sea un número positivo
bool validarCalificacion(double calificacion);      // Valida que la calificación esté entre 0 y 5

// Función para ingresar números de forma segura (sin plantilla)
bool ingresarNumero(int& numero);   // Para enteros (por ejemplo, año)
bool ingresarNumero(double& numero); // Para decimales (por ejemplo, precio o calificación)
// Declaración en Validaciones.h
bool ingresarOpcionMenu(int& opcion); // Función para validar la opción seleccionada en el menú
