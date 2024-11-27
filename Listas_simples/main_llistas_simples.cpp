/***********************************************************************
 * Module:  main_llistas_simples.cpp
 * Author:  Maycol Celi
 * Date: 27/11/2024
 * Purpose: Lista Simple de Personas
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Lista_Simple.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system("cls") o system("clear")
using namespace std;

// Funcion para limpiar la consola
void limpiarConsola() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear");
#endif
}


int main() {
    ListaSimple listaPrincipal;
    ListaSimple listaAuxiliar;
    string cedula, nombre, apellido;
    char caracter;
    int opcion;

    do {
        limpiarConsola();
        cout << "** Menu de opciones **\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter de nombre\n";
        cout << "6. Mostrar lista auxiliar\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        limpiarConsola();
        switch (opcion) {
            case 1: { // Insertar persona
                do {
                    cout << "Ingrese cedula: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else if (!validarCedulaUnica(cedula)) {
                        cout << "La cedula ya esta registrada. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Ingrese nombre: ";
                    cin.ignore(); // Limpia el buffer
                    getline(cin, nombre);
                    if (!validarSoloLetras(nombre)) {
                        cout << "Nombre invalido. Solo se permiten letras. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Ingrese apellido: ";
                    getline(cin, apellido);
                    if (!validarSoloLetras(apellido)) {
                        cout << "Apellido invalido. Solo se permiten letras. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                listaPrincipal.insertarACola(cedula, nombre, apellido);
                registrarCedula(cedula); // Registrar c�dula en el conjunto
                cout << "Persona registrada exitosamente.\n";

                break;
            }

            case 2: { // Buscar persona
                do {
                    cout << "Ingrese cedula a buscar: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else if (listaPrincipal.buscar(cedula) != nullptr) {
                    cout << "Persona encontrada.\n";
                } else {
                    cout << "Error: Persona no encontrada.\n";
                }

                break;
            }

            case 3: { // Eliminar persona
                do {
                    cout << "Ingrese cedula a eliminar: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else {
                    listaPrincipal.eliminar(cedula);
                    eliminarCedula(cedula); // Eliminar c�dula del conjunto
                    cout << "Persona eliminada exitosamente.\n";
                }

                break;
            }

            case 4: { // Mostrar lista principal
                listaPrincipal.mostrar();

                break;
            }

            case 5: { // Eliminar car�cter de nombre
                do {
                    cout << "Ingrese cedula: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else {
                    cout << "Ingrese caracter a eliminar: ";
                    cin >> caracter;
                    listaPrincipal.eliminarCaracter(cedula, caracter, listaAuxiliar);
                }

                break;
            }

            case 6: { // Mostrar lista auxiliar
                listaAuxiliar.mostrar();

                break;
            }

            case 7: { // Salir
                cout << "Saliendo...\n";

                break;
            }

            default: {
                cout << "Opcion invalida. Intente de nuevo.\n";

                break;
            }
        }
        system("pause");
    } while (opcion != 7);

    return 0;
}
