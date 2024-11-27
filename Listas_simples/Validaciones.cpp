#include "Validaciones.h"
#include <iostream>
#include <string>
#include <cctype>
#include <set>

using namespace std;

// Conjunto para almacenar las c�dulas �nicas
set<string> cedulasRegistradas;

bool validarCedulaReal(const string& cedula) {
    if (cedula.length() != 10) {
        cout << "Error: La cedula debe contener exactamente 10 digitos.\n";
        return false;
    }

    for (char c : cedula) {
        if (!isdigit(c)) {
            cout << "Error: La cedula debe contener solo numeros.\n";
            return false;
        }
    }

    // Algoritmo de validaci�n ecuatoriano
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) {
        cout << "Error: La cedula tiene un codigo de provincia invalido.\n";
        return false;
    }

    int digitoVerificador = cedula[9] - '0';
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) { // Posiciones impares
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int decenaSuperior = (suma + 9) / 10 * 10;
    int calculado = decenaSuperior - suma;

    if (calculado != digitoVerificador) {
        cout << "Error: La cedula no es valida.\n";
        return false;
    }

    return true;
}

bool validarCedulaUnica(const string& cedula) {
    if (cedulasRegistradas.find(cedula) != cedulasRegistradas.end()) {
        cout << "Error: La cedula ya esta registrada.\n";
        return false;
    }
    return true;
}

void registrarCedula(const string& cedula) {
    cedulasRegistradas.insert(cedula);
}

void eliminarCedula(const string& cedula) {
    cedulasRegistradas.erase(cedula);
}

bool validarSoloLetras(const string& texto) {
    for (char c : texto) {
        if (!isalpha(c) && c != ' ') {
            //cout << "Error: El texto debe contener solo letras.\n";
            return false;
        }
    }
    return true;
}

bool existeCedula(const string& cedula) {
    return cedulasRegistradas.find(cedula) != cedulasRegistradas.end();
}
