#include "ListasCirculares.h"
#include "Validaciones.h"
#include <iostream>
using namespace std;

int main() {
    ListaCircular lista;
    string nombre, apellido;
    long int cedulaNumerica;
    char caracter;
    int opcion;

    do {
        cout << "\n*** Menu de opciones ***\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Ingreso de cédula
                cedulaNumerica = ingresarCedulaNumerica();
                if (!validarCedulaReal(cedulaNumerica)) {
                    imprimirResultadoCedula(false);
                    break;
                }
                imprimirResultadoCedula(true);

                // Ingreso de nombre
                cout << "Ingrese nombre: ";
                cin >> nombre;
                if (!validarSoloLetras(nombre)) {
                    cout << "Error: El nombre debe contener solo letras.\n";
                    break;
                }

                // Ingreso de apellido
                cout << "Ingrese apellido: ";
                cin >> apellido;
                if (!validarSoloLetras(apellido)) {
                    cout << "Error: El apellido debe contener solo letras.\n";
                    break;
                }

                // Inserción en la lista
                lista.insertar(to_string(cedulaNumerica), nombre, apellido);
                break;
            }

            case 2:
                cout << "Ingrese cedula a buscar: ";
                cin >> cedulaNumerica;
                if (lista.buscar(to_string(cedulaNumerica)) != nullptr) {
                    Nodo* encontrado = lista.buscar(to_string(cedulaNumerica));
                    cout << "Persona encontrada: <Cedula: " << encontrado->getCedula()
                         << ", Nombre: " << encontrado->getNombre()
                         << ", Apellido: " << encontrado->getApellido() << ">\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;

            case 3:
                cout << "Ingrese cedula a eliminar: ";
                cin >> cedulaNumerica;
                lista.eliminar(to_string(cedulaNumerica));
                break;

            case 4:
                lista.mostrar();
                break;

            case 5:
                cout << "Ingrese cedula de la persona: ";
                cin >> cedulaNumerica;
                cout << "Ingrese caracter a eliminar: ";
                cin >> caracter;
                lista.eliminarCaracter(to_string(cedulaNumerica), caracter);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no valida. Intente nuevamente.\n";
        }
        system("pause");
    } while (opcion != 6);

    return 0;
}
