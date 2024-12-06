#include "ListaAutores.h"
#include "ListaLibros.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system()
#include <limits>


using namespace std;

// Función para limpiar la pantalla
void limpiarPantalla() {
    cout << string(50, '\n');
}

// Función para pausar el sistema y esperar una tecla
void pausarSistema() {
    cout << "Presione Enter para continuar... ";
    cin.ignore(); // Ignora cualquier entrada previa en el buffer
    getchar();    // Espera a que el usuario presione una tecla
}

// Menú para manejar las opciones de "Autores"
void menuAutores(ListaAutores& listaAutores) {
    int opcion;
    do {
        // Imprimir el menú de autores
        cout << "\n--- Menú de Autores ---\n";
        cout << "1. Insertar Autor\n";
        cout << "2. Buscar Autor\n";
        cout << "3. Eliminar Autor\n";
        cout << "4. Mostrar Autores\n";
        cout << "5. Volver al menú principal\n";
        cout << "Ingrese una opción: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opción no válida. Intente de nuevo.\n";
            pausarSistema();
            limpiarPantalla();
            continue;
        }

        switch (opcion) {
        case 1: {
            string cedula, nombre, apellido, fechaPublicacion;
            cout << "Ingrese cédula: ";
            cin >> cedula;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellido: ";
            cin >> apellido;
            cout << "Ingrese fecha de publicación (MM/dd/yyyy): ";
            cin >> fechaPublicacion;

            if (!validarCedula(cedula) || !validarTexto(nombre) || !validarTexto(apellido) || !validarFecha(fechaPublicacion)) {
                cout << "Error: Datos inválidos.\n";
                break;
            }
            listaAutores.insertar(cedula, nombre, apellido, fechaPublicacion);
            break;
        }
        case 2: {
            string cedula;
            cout << "Ingrese cédula del autor: ";
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
            cout << "Ingrese cédula del autor a eliminar: ";
            cin >> cedula;
            listaAutores.eliminar(cedula);
            break;
        }
        case 4:
            listaAutores.mostrar();
            break;
        case 5:
            cout << "Volviendo al menú principal...\n";
            break;
        }

        // Pausar después de procesar la opción
        pausarSistema();
        limpiarPantalla();

    } while (opcion != 5);
}

// Menú para manejar las opciones de "Libros"
void menuLibros(ListaLibros& listaLibros, ListaAutores& listaAutores) {
    int opcion;
    do {
        // Imprimir el menú de libros
        cout << "\n--- Menú de Libros ---\n";
        cout << "1. Insertar Libro\n";
        cout << "2. Buscar Libro\n";
        cout << "3. Eliminar Libro\n";
        cout << "4. Mostrar Libros\n";
        cout << "5. Volver al menú principal\n";
        cout << "Ingrese una opción: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opción no válida. Intente de nuevo.\n";
            pausarSistema();
            limpiarPantalla();
            continue;
        }

        switch (opcion) {
        case 1: {
            string titulo, isbn, genero, anioLanzamiento;
            double precio, calificacion;

            string autor = listaLibros.seleccionarAutor(listaAutores);
            if (autor.empty()) break;

            cout << "Ingrese título: ";
            cin >> titulo;
            cout << "Ingrese ISBN: ";
            cin >> isbn;
            cout << "Ingrese género: ";
            cin >> genero;
            cout << "Ingrese año de lanzamiento: ";
            cin>> anioLanzamiento;
            cout << "Ingrese precio: ";
            ingresarNumero(precio);
            if (!validarPrecio(precio)) {
                cout << "Error: El precio debe ser positivo.\n";
                break;
            }
            cout << "Ingrese calificación (0-10): ";
            ingresarNumero(calificacion);
            if (!validarCalificacion(calificacion)) {
                cout << "Error: La calificación debe ser entre 0 y 10.\n";
                break;
            }

            listaLibros.insertar(titulo, autor, isbn, anioLanzamiento, genero, precio, calificacion);
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
            cout << "Volviendo al menú principal...\n";
            break;
        }

        // Pausar después de procesar la opción
        pausarSistema();
        limpiarPantalla();

    } while (opcion != 5);
}

int main() {
    ListaLibros listaLibros;
    ListaAutores listaAutores;
   
    listaAutores.cargarDesdeArchivoJSON();
    listaLibros.cargarDesdeArchivoJSON();
    
    int opcionMenu;

    do {
        cout << "--- Menú Principal ---\n";
        cout << "1. Manejar Autores\n";
        cout << "2. Manejar Libros\n";
        cout << "3. Salir\n";
        cout << "Ingrese una opción: ";
        ingresarOpcionMenu(opcionMenu);

        if (!validarOpcionMenu(opcionMenu, 1, 3)) {
            cout << "Opción no válida. Intente de nuevo.\n";
            pausarSistema();
            limpiarPantalla();
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
