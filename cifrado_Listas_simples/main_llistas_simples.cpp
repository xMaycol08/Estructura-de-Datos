/***********************************************************************
 * Module:  main_llistas_simples.cpp
 * Author:  Maycol Celi
 * Date: 28/11/2024
 * Purpose: Lista simple - Personas
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Lista_Simple.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib>
using namespace std;


void limpiarConsola() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}


int main() {
    ListaSimple listaPrincipal;
    ListaSimple listaAuxiliar;
    string cedula, nombre, apellido;
    int desplazar;
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
        cout << "6. Cifrar un caracter\n";
        cout << "7. Mostrar lista auxiliar\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        limpiarConsola();
        switch (opcion) {
            case 1: {
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
                    cin >> nombre;
                    if (!validarSoloLetras(nombre)) {
                        cout << "Error: El nombre debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!validarSoloLetras(nombre));

                do {
                    cout << "Ingrese apellido: ";
                    cin >> apellido;
                    if (!validarSoloLetras(apellido)) {
                        cout << "Error: El apellido debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!validarSoloLetras(apellido));

                listaPrincipal.insertarACola(cedula, nombre, apellido);
                registrarCedula(cedula);
                break;
            }

            case 2: {
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

            case 3: {
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
                    eliminarCedula(cedula); // Eliminar cedula del conjunto
                    cout << "Persona eliminada exitosamente.\n";
                }
                break;
            }

            case 4: {
                listaPrincipal.mostrar();
                break;
            }

            case 5: {
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
            case 6:{
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
                    cout << "Ingrese caracter a crifrar: ";
                    cin >> caracter;

                    cout<< "Ingrese el desplazamieno: ";
                    cin>>desplazar;
                    listaPrincipal.cifrarCaracter(cedula,caracter,desplazar, listaAuxiliar);
                }
                break;

            }

            case 7: {
                listaAuxiliar.mostrar();
                break;
            }

            case 8: {
                cout << "Salio del programa con exito\n";
                exit(0);
                break;
            }

            default: {
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
            }
        }
        system("pause");
    } while (opcion != 8);

    return 0;
}
