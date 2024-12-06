#pragma once
#include <string>
using namespace std;

bool validarCedula(const string& cedula);
bool validarTexto(const string& texto);
bool validarFecha(const string& fecha);
bool validarEntero(const string& numero);
bool validarFlotante(const string& numero);
bool validarOpcionMenu(int opcion, int min, int max);
bool validarPrecio(double precio);
bool validarCalificacion(double calificacion);

// Funciones para ingresar números de forma segura
bool ingresarNumero(int& numero);         // Para enteros (por ejemplo, año)
bool ingresarNumero(double& numero);      // Para decimales (por ejemplo, precio o calificación)
bool ingresarOpcionMenu(int& opcion);     // Función para validar la opción seleccionada en el menú
