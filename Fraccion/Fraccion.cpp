/***********************************************************************
 * Module:  Fraccion.cpp
 * Author:  Maycol Celi
 * Date: 11/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Fraccion.h"
#include <stdexcept>

// Constructor
template <typename T>
Fraccion<T>::Fraccion(T numerador, T denominador) : numerador(numerador), denominador(denominador) {
    if (denominador == 0) {
        throw std::invalid_argument("El denominador no puede ser cero.");
    }
}

// Destructor
template <typename T>
Fraccion<T>::~Fraccion() {}

// Setters
template <typename T>
void Fraccion<T>::setNumerador(T numerador) {
    this->numerador = numerador;
}

// Getters
template <typename T>
T Fraccion<T>::getNumerador() const {
    return numerador;
}

template <typename T>
T Fraccion<T>::getDenominador() const {
    return denominador;
}

// Método para procesar la suma de dos fracciones
template <typename T>
Fraccion<T> Fraccion<T>::procesarSuma(const Fraccion<T>& obj1, const Fraccion<T>& obj2) {
    T nuevoNumerador = obj1.numerador * obj2.denominador + obj2.numerador * obj1.denominador;
    T nuevoDenominador = obj1.denominador * obj2.denominador;
    return Fraccion<T>(nuevoNumerador, nuevoDenominador);
}

// Método para procesar la resta de dos fracciones
template <typename T>
Fraccion<T> Fraccion<T>::procesarResta(const Fraccion<T>& obj1, const Fraccion<T>& obj2) {
    T nuevoNumerador = obj1.numerador * obj2.denominador - obj2.numerador * obj1.denominador;
    T nuevoDenominador = obj1.denominador * obj2.denominador;
    return Fraccion<T>(nuevoNumerador, nuevoDenominador);
}

// Método para procesar la multiplicación de dos fracciones
template <typename T>
Fraccion<T> Fraccion<T>::procesarMultiplicacion(const Fraccion<T>& obj1, const Fraccion<T>& obj2) {
    T nuevoNumerador = obj1.numerador * obj2.numerador;
    T nuevoDenominador = obj1.denominador * obj2.denominador;
    return Fraccion<T>(nuevoNumerador, nuevoDenominador);
}

