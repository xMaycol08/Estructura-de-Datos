/***********************************************************************
 * Module:  main.cpp
 * Author:  Maycol Celi.
 * Date: 01/12/2024
 * Purpose: Codigo Polaca
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Función para verificar si un carácter es un operador
bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Función para evaluar una operación
int evaluarOperacion(char operador, int operando1, int operando2) {
    switch (operador) {
        case '+': return operando1 + operando2;
        case '-': return operando1 - operando2;
        case '*': return operando1 * operando2;
        case '/': 
            if (operando2 == 0) {
                throw runtime_error("Error: División por cero.");
            }
            return operando1 / operando2;
        default: 
            throw runtime_error("Operador desconocido.");
    }
}

// Función para evaluar una expresión en notación prefija
int evaluarPrefija(const string& expresion) {
    stack<int> pila;
    stringstream ss(expresion);
    string token;
    
    // Dividimos la expresión en tokens y procesamos de derecha a izquierda
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        token = *it;
        if (esOperador(token[0]) && token.size() == 1) {
            // Es un operador, sacamos dos operandos de la pila
            if (pila.size() < 2) {
                throw runtime_error("Expresión inválida.");
            }
            int operando1 = pila.top(); pila.pop();
            int operando2 = pila.top(); pila.pop();
            int resultado = evaluarOperacion(token[0], operando1, operando2);
            pila.push(resultado);
        } else {
            // Es un operando, lo convertimos a entero y lo apilamos
            pila.push(stoi(token));
        }
    }
    
    if (pila.size() != 1) {
        throw runtime_error("Expresión inválida.");
    }
    return pila.top();
}

int main() {
    string expresion;
    
    cout << "Introduce la expresión en notación prefija (ejemplo: + 5 * 3 2): ";
    getline(cin, expresion);
    
    try {
        int resultado = evaluarPrefija(expresion);
        cout << "Resultado: " << resultado << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    
    return 0;
}
