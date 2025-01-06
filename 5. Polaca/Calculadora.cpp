#include "Calculadora.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>

int Calculadora::obtenerPrecedencia(char operador)
{
    try {
        if (operador == '+' || operador == '-')
            return 1;
        if (operador == '*' || operador == '/')
            return 2;
        return 0;
    } catch (const exception &e) {
        throw runtime_error("Error al obtener la precedencia del operador.");
    }
}

bool Calculadora::esOperador(char c)
{
    try {
        return c == '+' || c == '-' || c == '*' || c == '/';
    } catch (const exception &e) {
        throw runtime_error("Error al verificar si el caracter es un operador.");
    }
}

bool Calculadora::esExpresionValida(const string &expresion)
{
    try {
        int operandos = 0;
        int operadores = 0;
        for (char c : expresion)
        {
            if (isalnum(c))
            {
                operandos++;
            }
            else if (esOperador(c))
            {
                operadores++;
            }
            else if (c != '(' && c != ')')
            {
                return false;
            }
        }
        return operandos >= 2 && operadores >= 1;
    } catch (const exception &e) {
        throw runtime_error("Error al validar la expresion.");
    }
}

bool Calculadora::tieneParentesisBalanceados(const string &expresion)
{
    try {
        int contador = 0;
        for (char c : expresion)
        {
            if (c == '(')
                contador++;
            else if (c == ')')
            {
                contador--;
                if (contador < 0)
                    return false;
            }
        }
        return contador == 0;
    } catch (const exception &e) {
        throw runtime_error("Error al verificar el balance de parentesis.");
    }
}

bool Calculadora::esSecuenciaValida(const string &expresion)
{
    try {
        char ultimoCaracter = '\0';
        for (char c : expresion)
        {
            if (esOperador(c) && (ultimoCaracter == '\0' || esOperador(ultimoCaracter)))
            {
                return false;
            }
            if (isalnum(c) || c == '(' || c == ')')
            {
                ultimoCaracter = c;
            }
        }
        return !esOperador(ultimoCaracter);
    } catch (const exception &e) {
        throw runtime_error("Error al verificar la secuencia de la expresion.");
    }
}

string Calculadora::eliminarEspacios(const string &expresion)
{
    try {
        string sinEspacios;
        for (char c : expresion)
        {
            if (!isspace(c))
            {
                sinEspacios += c;
            }
        }
        return sinEspacios;
    } catch (const exception &e) {
        throw runtime_error("Error al eliminar espacios de la expresion.");
    }
}

string Calculadora::infijoAPostfijo(const string &expresion)
{
    try {
        stack<char> pila;
        string resultado;

        for (char c : expresion)
        {
            if (isalnum(c))
            {
                resultado += c;
            }
            else if (c == '(')
            {
                pila.push(c);
            }
            else if (c == ')')
            {
                while (!pila.empty() && pila.top() != '(')
                {
                    resultado += pila.top();
                    pila.pop();
                }
                pila.pop();
            }
            else if (esOperador(c))
            {
                while (!pila.empty() && obtenerPrecedencia(pila.top()) >= obtenerPrecedencia(c))
                {
                    resultado += pila.top();
                    pila.pop();
                }
                pila.push(c);
            }
        }

        while (!pila.empty())
        {
            resultado += pila.top();
            pila.pop();
        }

        return resultado;
    } catch (const exception &e) {
        throw runtime_error("Error al convertir de infijo a postfijo.");
    }
}

string Calculadora::infijoAPrefijo(const string &expresion)
{
    try {
        string expresionReversa = expresion;
        reverse(expresionReversa.begin(), expresionReversa.end());

        for (char &c : expresionReversa)
        {
            if (c == '(')
                c = ')';
            else if (c == ')')
                c = '(';
        }

        string postfijo = infijoAPostfijo(expresionReversa);
        reverse(postfijo.begin(), postfijo.end());

        return postfijo;
    } catch (const exception &e) {
        throw runtime_error("Error al convertir de infijo a prefijo.");
    }
}

string Calculadora::convertir(int opcion, const string &expresionOriginal)
{
    try {
        string expresion = eliminarEspacios(expresionOriginal);

        if (expresion.empty())
            throw runtime_error("La expresion no puede estar vacia.");
        if (expresion.length() > 100)
            throw runtime_error("La expresion es demasiado larga.");
        if (!esExpresionValida(expresion))
            throw runtime_error("La expresion debe tener al menos un operador y dos operandos.");
        if (!tieneParentesisBalanceados(expresion))
            throw runtime_error("La expresion no tiene parentesis balanceados.");
        if (!esSecuenciaValida(expresion))
            throw runtime_error("La secuencia de operadores y operandos no es valida.");

        switch (opcion)
        {
        case 1:
            return infijoAPrefijo(expresion);
        case 2:
            return infijoAPostfijo(expresion);
        default:
            throw runtime_error("Opcion invalida.");
        }
    } catch (const exception &e) {
        throw runtime_error("Error al convertir la expresion: " + string(e.what()));
    }
}
