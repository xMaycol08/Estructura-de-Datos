/***********************************************************************
 * Module:  main.cpp
 * Author:  Maycol Celi.
 * Date: 01/12/2024
 * Purpose: Codigo Polaca
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include <iostream>
#include <conio.h> // Para getch()
#include "CalculadoraPolaca.h"

using namespace std;

int main() {
    string infijoExpresion;
    char tecla;
    char ultimaTecla = '\0'; // Almacena el último carácter ingresado

    do{
        cout << "Ingrese una expresion infija valida (solo se permiten numeros, +, -, *, /, (, )):";

        while (true) {
            tecla = getch(); // Captura una tecla sin mostrarla en consola

            if (tecla == '\r') { // Enter para finalizar la entrada
                cout << endl;
                break;
            } else if (tecla == '\b') { // Retroceso
                if (!infijoExpresion.empty()) {
                    infijoExpresion.pop_back();
                    ultimaTecla = infijoExpresion.empty() ? '\0' : infijoExpresion.back();
                    cout << "\b \b"; // Borra el ultimo caracter en consola
                }
            } else if (isdigit(tecla) || tecla == '(' || tecla == ')') {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime caracteres validos
            } else if (Calculadora::esOperador(tecla) && !Calculadora::esOperador(ultimaTecla)) {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime el operador si el ultimo caracter no es otro operador
            }
        }
        if (!Calculadora::esExpresionValida(infijoExpresion)) {
            cout << "\nExpresion invalida. Asegurese de usar al menos dos numeros con un operador y que los operadores no esten consecutivos.\n";
        }else{
            break;
        }

    }while(true);

    string posfijaExpresion = Calculadora::infijaAPosfija(infijoExpresion);
    string prefijaExpresion = Calculadora::infijaAPrefija(infijoExpresion);

    cout << "Expresion infija: " << infijoExpresion << endl;
    cout << "Expresion posfija: " << posfijaExpresion << endl;
    cout << "Expresion prefija: " << prefijaExpresion << endl;

    return 0;
}
