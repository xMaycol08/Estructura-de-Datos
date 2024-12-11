/***********************************************************************
 * Module:  mainFraccion.cpp
 * Author:  Maycol Celi
 * Date: 11/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Fraccion.cpp"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <conio.h> // Para usar getch()
#include <cstdlib> // Para la función atoi

using namespace std;

// Función para ingresar un número entero validando la entrada
int ingresar_entero(const char *mensaje) {
    char num[10];
    char c;
    int i = 0;
    int valor;

    cout << mensaje;

    while ((c = getch()) != 13) { // Mientras no se presione Enter
        if ((c >= '0' && c <= '9') || (c == '-' && i == 0)) { // Si es un número o un signo menos al inicio
            if (i < 9) { // Verifica que no exceda el tamaño del buffer
                cout << c; // Muestra el carácter
                num[i++] = c; // Agrega al arreglo
            }
        } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
            cout << "\b \b"; // Retrocede, borra el carácter en pantalla
            i--; // Reduce el índice para eliminar el último carácter ingresado
        }
        // No se muestra ni permite otros caracteres (como letras o símbolos no válidos)
    }

    num[i] = '\0'; // Termina la cadena
    valor = atoi(num); // Convierte la cadena a entero

    return valor;
}

int main() {
    try {
        int numerador1, denominador1, numerador2, denominador2;

        // Solicitar y validar la primera fracción
        numerador1 = ingresar_entero("Ingrese el numerador de la primera fraccion: ");
        while (numerador1 == 0) {  // Validación del denominador no puede ser 0
            cout << "Entrada no valida. Ingrese un numero entero: ";
            numerador1 = ingresar_entero("Ingrese el numerador de la primera fraccion: ");
        }

        denominador1 = ingresar_entero("Ingrese el denominador de la primera fraccion (no puede ser 0): ");
        while (denominador1 == 0) {
            cout << "El denominador no puede ser cero. Intente de nuevo: ";
            denominador1 = ingresar_entero("Ingrese el denominador de la primera fraccion (no puede ser 0): ");
        }

        // Solicitar y validar la segunda fracción
        numerador2 = ingresar_entero("Ingrese el numerador de la segunda fraccion: ");
        while (numerador2 == 0) {  // Validación del denominador no puede ser 0
            cout << "Entrada no valida. Ingrese un numero entero: ";
            numerador2 = ingresar_entero("Ingrese el numerador de la segunda fraccion: ");
        }

        denominador2 = ingresar_entero("Ingrese el denominador de la segunda fraccion (no puede ser 0): ");
        while (denominador2 == 0) {
            cout << "El denominador no puede ser cero. Intente de nuevo: ";
            denominador2 = ingresar_entero("Ingrese el denominador de la segunda fraccion (no puede ser 0): ");
        }

        // Crear objetos Fraccion
        Fraccion<int> fraccion1(numerador1, denominador1);
        Fraccion<int> fraccion2(numerador2, denominador2);

        // Operación de suma
        Fraccion<int> resultadoSuma = fraccion1.procesarSuma(fraccion1, fraccion2);
        cout << "La suma de las fracciones "
             << fraccion1.getNumerador() << "/" << fraccion1.getDenominador()
             << " + "
             << fraccion2.getNumerador() << "/" << fraccion2.getDenominador()
             << " es: "
             << resultadoSuma.getNumerador() << "/" << resultadoSuma.getDenominador()
             << endl;
        double resultadoDecimalSuma = static_cast<double>(resultadoSuma.getNumerador()) / resultadoSuma.getDenominador();
        cout << "El resultado en decimal es: " << resultadoDecimalSuma << endl;

        // Operación de resta
        Fraccion<int> resultadoResta = fraccion1.procesarResta(fraccion1, fraccion2);
        cout << "La resta de las fracciones "
             << fraccion1.getNumerador() << "/" << fraccion1.getDenominador()
             << " - "
             << fraccion2.getNumerador() << "/" << fraccion2.getDenominador()
             << " es: "
             << resultadoResta.getNumerador() << "/" << resultadoResta.getDenominador()
             << endl;
        double resultadoDecimalResta = static_cast<double>(resultadoResta.getNumerador()) / resultadoResta.getDenominador();
        cout << "El resultado en decimal es: " << resultadoDecimalResta << endl;

        // Operación de multiplicación
        Fraccion<int> resultadoMultiplicacion = fraccion1.procesarMultiplicacion(fraccion1, fraccion2);
        cout << "La multiplicacion de las fracciones "
             << fraccion1.getNumerador() << "/" << fraccion1.getDenominador()
             << " * "
             << fraccion2.getNumerador() << "/" << fraccion2.getDenominador()
             << " es: "
             << resultadoMultiplicacion.getNumerador() << "/" << resultadoMultiplicacion.getDenominador()
             << endl;
        double resultadoDecimalMultiplicacion = static_cast<double>(resultadoMultiplicacion.getNumerador()) / resultadoMultiplicacion.getDenominador();
        cout << "El resultado en decimal es: " << resultadoDecimalMultiplicacion << endl;

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
