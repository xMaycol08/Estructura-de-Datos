/***********************************************************************
 * Module:  main.cpp
 * Authors:  Erika Guayanay, Yerson Llumiquinga, Maycol Celi.
 * Date: 30/11/2024
 * Purpose: Lista Autores de Libros
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListaCircularDoble.h"
#include <iostream>
#include <limits>
using namespace std;

// Limpiar consola según el sistema operativo
void limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Menú principal
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
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string titulo, autor, isbn, genero, sinopsis;
                int anio;
                double precio, calificacion;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el titulo del libro: ";
                getline(cin, titulo);

                cout << "Ingrese el autor del libro: ";
                getline(cin, autor);

                cout << "Ingrese el ano de publicacion: ";
                cin >> anio;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                cout << "Ingrese el ISBN (unico): ";
                getline(cin, isbn);

                cout << "Ingrese el genero del libro: ";
                getline(cin, genero);

                cout << "Ingrese la sinopsis del libro: ";
                getline(cin, sinopsis);

                cout << "Ingrese el precio del libro: ";
                cin >> precio;

                cout << "Ingrese la calificación del libro (0 a 5): ";
                cin >> calificacion;

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
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
        }

       system("pause");
    } while (opcion != 5);

    return 0;
}
