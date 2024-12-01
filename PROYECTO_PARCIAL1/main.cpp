/***********************************************************************
 * Module:  main.cpp
 * Authors:  Erika Guayanay, Yerson Llumiquinga, Maycol Celi.
 * Date: 30/11/2024
 * Purpose: Lista Autores de Libros
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListaCircularDoble.h"
#include "Validaciones.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <hpdf.h>
#include "GenerarPDF.h"
using namespace std;

// Limpiar consola según el sistema operativo
void limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {

    ListaCircularDoble lista;
    int opcion;

    do {
        limpiarConsola();
        cout << "\n*** Biblioteca Digital ***\n";
        cout << "1. Insertar libro\n";
        cout << "2. Buscar libro por ISBN\n";
        cout << "3. Eliminar libro por ISBN\n";
        cout << "4. Mostrar todos los libros\n";
        cout << "5. Generar PDF\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
         // Validar que la opción ingresada sea un número entero
        while (!ingresarOpcionMenu(opcion)) {
            cout << "Error: Ingrese solo un numero entre el 1 y el 5: ";
        }

        switch (opcion) {
            case 1: {
                string titulo, autor, isbn, genero, sinopsis;
                int anio;
                double precio, calificacion;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el titulo del libro: ";
                getline(cin, titulo);
                while (!validarTexto(titulo)) {
                    cout << "Error: El titulo solo debe contener letras y espacios. Intente nuevamente: ";
                    getline(cin, titulo);
                }

                cout << "Ingrese el autor del libro: ";
                getline(cin, autor);
                while (!validarTexto(autor)) {
                    cout << "Error: El autor solo debe contener letras y espacios. Intente nuevamente: ";
                    getline(cin, autor);
                }

                cout << "Ingrese el ano de publicacion: ";
                while (true) {
                    if (ingresarNumero(anio) && validarAnioPublicacion(anio)) {
                        break; // Si la entrada es válida, salimos del bucle
                    }
                    cout << "Error: El ano debe ser un numero entre 1800 y 2024. Intente nuevamente: ";
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el ISBN (unico): ";
                getline(cin, isbn);
                while (!validarISBN(isbn)) {
                    cout << "Error: El ISBN solo debe contener numeros y guiones. Intente nuevamente: ";
                    getline(cin, isbn);
                }

                cout << "Ingrese el genero del libro: ";
                getline(cin, genero);
                while (!validarTexto(genero)) {
                    cout << "Error: El genero solo debe contener letras y espacios. Intente nuevamente: ";
                    getline(cin, genero);
                }

                cout << "Ingrese la sinopsis del libro: ";
                getline(cin, sinopsis);
                while (!validarTexto(sinopsis)) {
                    cout << "Error: La sinopsis solo debe contener letras y espacios. Intente nuevamente: ";
                    getline(cin, sinopsis);
                }

                cout << "Ingrese el precio del libro: ";
                while (true) {
                    if (ingresarNumero(precio) && validarPrecio(precio)) {
                        break; // Si la entrada es válida, salimos del bucle
                    }
                    cout << "Error: El precio debe ser un numero mayor a 0. Intente nuevamente: ";
                }

                cout << "Ingrese la calificacion del libro (0 a 5): ";
                while (true) {
                    if (ingresarNumero(calificacion) && validarCalificacion(calificacion)) {
                        break; // Si la entrada es válida, salimos del bucle
                    }
                    cout << "Error: La calificacion debe ser un numero entre 0 y 5. Intente nuevamente: ";
                }

                lista.insertar(titulo, autor, anio, isbn, genero, sinopsis, precio, calificacion);
                break;
            }

            case 2: {
                string isbn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el ISBN del libro a buscar: ";
                getline(cin, isbn);

                NodoLibro* libro = lista.buscar(isbn);
                if (libro) {
                    cout << "\nLibro encontrado:\n";
                    cout << "Titulo: " << libro->getTitulo() << "\n";
                    cout << "Autor: " << libro->getAutor() << "\n";
                    cout << "Ano de Publicacion: " << libro->getAnioPublicacion() << "\n";
                    cout << "ISBN: " << libro->getISBN() << "\n";
                    cout << "Genero: " << libro->getGenero() << "\n";
                    cout << "Sinopsis: " << libro->getSinopsis() << "\n";
                    cout << "Precio: $" << libro->getPrecio() << "\n";
                    cout << "Calificacion: " << libro->getCalificacion() << "/5\n";
                } else {
                    cout << "No se encontro un libro con ese ISBN.\n";
                }
                break;
            }

            case 3: {
                string isbn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el ISBN del libro a eliminar: ";
                getline(cin, isbn);

                if (lista.eliminar(isbn)) {
                    cout << "Libro eliminado correctamente.\n";
                }
                break;
            }

            case 4:
                cout << "\nLista de libros:\n";
                lista.mostrar();
                break;

            case 5:
                generarPDF(lista);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;


            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
        }

        system("pause");
    } while (opcion != 6);

    return 0;
}
