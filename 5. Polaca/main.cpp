/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
 * ALUMNOS:  Erika Guayanay,Jerson Llumiquinga,Maycol Celi
 * FECHA ENTREGA:  11 de noviembre de 2024
 * PROGRAMA: Calculadora Polaca.
 * NRC: 1992
 ***********************************************************************/
#include "Calculadora.cpp"
#include "Validaciones.cpp"
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

using namespace std;

int main()
{
    try {
        Calculadora calculadora;
        string expresion;
        int opcion;

        while (true)
        {
            cout << "Conversor de Notacion Matematica" << endl;
            cout << "1. Infijo a Prefijo" << endl;
            cout << "2. Infijo a Postfijo" << endl;
            cout << "3. Salir" << endl;

            cout << "\nSeleccione una opcion (1-3): ";
            opcion = obtenerOpcion();

            if (opcion == -1 || opcion < 1 || opcion > 3)
            {
                cout << "\nOpcion invalida. Introduzca un numero entre 1 y 3." << endl;
                // Pause and clear the console
                cout << "Presione cualquier tecla para continuar...";
                _getch();
                system(CLEAR);
                continue;
            }

            if (opcion == 3)
            {
                cout << "\nSaliendo del programa..." << endl;
                break;
            }

            cout << "\nIntroduzca la expresion: ";
            expresion = obtenerExpresion();

            if (expresion.empty()) {
                cout << "\nLa expresion no puede estar vacia." << endl;
                // Pause and clear the console
                cout << "Presione cualquier tecla para continuar...";
                _getch();
                system(CLEAR);
                continue;
            }

            try
            {
                string resultado = calculadora.convertir(opcion, expresion);
                if (opcion == 1) {
                    cout << "\nResultado de Infijo a Prefijo: " << resultado << endl;
                } else if (opcion == 2) {
                    cout << "\nResultado de Infijo a Postfijo: " << resultado << endl;
                }
            }
            catch (const runtime_error &e)
            {
                cerr << "\n" << e.what() << endl;
            }

            // Pause and clear the console
            cout << "\nPresione cualquier tecla para continuar...";
            _getch();
            system(CLEAR);
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
