#include "ListaAutores.h"
#include "ListaLibros.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system()
#include <limits>
#include <hpdf.h>
#include "GenerarPDFLibros.h"
#include "GenerarPDFAutores.h"

// Men� para manejar las opciones de "Autores"
void menuAutores(ListaAutores& listaAutores) {
    int opcion;
    do {
        system("pause");
        system("cls");
        // Imprimir el men� de autores
        cout << "\n--- Men� de Autores ---\n";
        cout << "1. Insertar Autor\n";
        cout << "2. Buscar Autor\n";
        cout << "3. Eliminar Autor\n";
        cout << "4. Mostrar Autores\n";
        cout << "5. Generar PDF Autores\n";
        cout << "6. Volver al men� principal\n";
        cout << "Ingrese una opci�n: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opci�n no v�lida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
        case 1: {
            string cedula, nombre, apellido, fechaPublicacion;
            cout << "Ingrese c�dula: ";
            cin >> cedula;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellido: ";
            cin >> apellido;
            cout << "Ingrese fecha de publicaci�n (MM/dd/yyyy): ";
            cin >> fechaPublicacion;

            if (!validarCedula(cedula) || !validarTexto(nombre) || !validarTexto(apellido) || !validarFecha(fechaPublicacion)) {
                cout << "Error: Datos inv�lidos.\n";
                break;
            }
            listaAutores.insertar(cedula, nombre, apellido, fechaPublicacion);
            break;
        }
        case 2: {
            string cedula;
            cout << "Ingrese c�dula del autor: ";
            cin >> cedula;
            NodoAutores* autor = listaAutores.buscar(cedula);
            if (autor) {
                cout << "Autor encontrado: " << autor->getNombre() << " " << autor->getApellido() << "\n";
            } else {
                cout << "Autor no encontrado.\n";
            }
            break;
        }
        case 3: {
            string cedula;
            cout << "Ingrese c�dula del autor a eliminar: ";
            cin >> cedula;
            listaAutores.eliminar(cedula);
            break;
        }
        case 4:
            listaAutores.mostrar();
            break;
        case 5:
            {
                        GenerarPDFAutores generador(listaAutores);
    generador.generarPDF("autores_lista.pdf");
            }

            break;
        case 6:
            cout << "Volviendo al men� principal...\n";
            system("pause");
            break;
        }

    } while (opcion != 6);
}

// Men� para manejar las opciones de "Libros"
void menuLibros(ListaLibros& listaLibros, ListaAutores& listaAutores) {
    int opcion;
    do {
        system("pause");
        system("cls");
        // Imprimir el men� de libros
        cout << "\n--- Men� de Libros ---\n";
        cout << "1. Insertar Libro\n";
        cout << "2. Buscar Libro\n";
        cout << "3. Eliminar Libro\n";
        cout << "4. Mostrar Libros\n";
        cout << "5. Generar PDF de Libros\n";
        cout << "6. Volver al men� principal\n";
        cout << "Ingrese una opci�n: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opci�n no v�lida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
        case 1: {
            string titulo, isbn, genero, anioLanzamiento;
            double precio, calificacion;

            string autor = listaLibros.seleccionarAutor(listaAutores);
            if (autor.empty()) break;

            cout << "Ingrese t�tulo: ";
            cin >> titulo;
            cout << "Ingrese ISBN: ";
            cin >> isbn;
            cout << "Ingrese g�nero: ";
            cin >> genero;
            cout << "Ingrese a�o de lanzamiento: ";
            cin>> anioLanzamiento;
            cout << "Ingrese precio: ";
            ingresarNumero(precio);
            if (!validarPrecio(precio)) {
                cout << "Error: El precio debe ser positivo.\n";
                break;
            }
            cout << "Ingrese calificaci�n (0-10): ";
            ingresarNumero(calificacion);
            if (!validarCalificacion(calificacion)) {
                cout << "Error: La calificaci�n debe ser entre 0 y 10.\n";
                break;
            }

            listaLibros.insertar(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
            break;
        }
        case 2: {
            string isbn;
            cout << "Ingrese ISBN del libro: ";
            cin >> isbn;
            NodoLibros* libro = listaLibros.buscar(isbn);
            if (libro) {
                cout << "Libro encontrado: " << libro->getTitulo() << " por " << libro->getAutor() << "\n";
            } else {
                cout << "Libro no encontrado.\n";
            }
            break;
        }
        case 3: {
            string isbn;
            cout << "Ingrese ISBN del libro a eliminar: ";
            cin >> isbn;
            listaLibros.eliminar(isbn);
            break;
        }
        case 4:
            listaLibros.mostrar();
            break;
        case 5:
            { GenerarPDFLibros generadorPDF(listaLibros);

    // Generar el archivo PDF con los libros
    generadorPDF.generarPDF("libros_lista.pdf");
            }
            break;
        case 6:
            cout << "Volviendo al men� principal...\n";
            system("pause");
            break;
        }
    } while (opcion != 6);
}

int main() {
    ListaLibros listaLibros;
    ListaAutores listaAutores;

    listaAutores.cargarDesdeArchivoJSON();
    listaLibros.cargarDesdeArchivoJSON();

    int opcionMenu;

    do {
        system("cls");
        cout << "--- Men� Principal ---\n";
        cout << "1. Manejar Autores\n";
        cout << "2. Manejar Libros\n";
        cout << "3. Salir\n";
        cout << "Ingrese una opci�n: ";
        ingresarOpcionMenu(opcionMenu);

        if (!validarOpcionMenu(opcionMenu, 1, 3)) {
            cout << "Opci�n no v�lida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionMenu) {
        case 1:
            menuAutores(listaAutores);
            break;
        case 2:
            menuLibros(listaLibros, listaAutores);
            break;
        case 3:
            cout << "Saliendo...\n";
            break;
        }
    } while (opcionMenu != 3);

    return 0;
}
