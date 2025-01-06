#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <string>
#include <stack>

using namespace std;

class Calculadora
{
public:
    string convertir(int opcion, const string &expresion);

private:
    int obtenerPrecedencia(char operador);
    bool esOperador(char c);
    bool esExpresionValida(const string &expresion);
    bool tieneParentesisBalanceados(const string &expresion);
    bool esSecuenciaValida(const string &expresion);
    string eliminarEspacios(const string &expresion);

    string infijoAPostfijo(const string &expresion);
    string infijoAPrefijo(const string &expresion);
};

#endif
