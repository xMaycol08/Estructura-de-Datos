#include "ListaLibros.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "json.hpp"
using json = nlohmann::json;

ListaLibros::ListaLibros() : cabeza(nullptr) {}

ListaLibros::~ListaLibros() {
    if (cabeza) {
        NodoLibros* actual = cabeza;
        do {
            NodoLibros* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

bool ListaLibros::insertar(string titulo, string autor, string isbn, string genero, string anioLanzamiento, float precio, float calificacion) {
    if (buscar(isbn)) {
        cout << "Error: Libro con ISBN " << isbn << " ya existe.\n";
        return false;
    }

    NodoLibros* nuevo = new NodoLibros(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        NodoLibros* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    return true;
}

NodoLibros* ListaLibros::buscar(string isbn) {
    if (!cabeza) {
        cout << "La lista de libros est� vac�a.\n";
        return nullptr;
    }

    NodoLibros* actual = cabeza;
    do {
        // Depuraci�n: Mostrar qu� ISBN se compara
        //cout << "Comparando ISBN en nodo: " << actual->getIsbn() << " con " << isbn << "\n";
        if (actual->getIsbn() == isbn) {
            cout << "Libro encontrado: " << actual->getTitulo() << "\n";
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    cout << "ISBN no encontrado: " << isbn << "\n";
    return nullptr;
}

bool ListaLibros::eliminar(string isbn) {
    // Verificar si la lista est� vac�a
    if (!cabeza) {
        cout << "Error: La lista de libros est� vac�a.\n";
        return false;
    }

    NodoLibros* encontrado = buscar(isbn); // Buscar el nodo a eliminar
    if (!encontrado) {
        cout << "Error: Libro con ISBN " << isbn << " no encontrado.\n";
        return false;
    }

    // Caso: �nico nodo en la lista
    if (encontrado->getSiguiente() == encontrado) {
        cabeza = nullptr;
    } else {
        // Caso: M�ltiples nodos en la lista
        NodoLibros* anterior = encontrado->getAnterior();
        NodoLibros* siguiente = encontrado->getSiguiente();

        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);

        // Actualizar la cabeza si es necesario
        if (cabeza == encontrado) {
            cabeza = siguiente;
        }
    }

    // Eliminar el nodo
    cout << "Eliminando libro: " << encontrado->getTitulo() << ", ISBN: " << encontrado->getIsbn() << "\n";
    delete encontrado;

    guardarEnArchivoJSON(); // Actualizar el archivo JSON
    return true;
}

void ListaLibros::mostrar() {
    if (!cabeza) {
        cout << "Lista de libros vac�a.\n";
        return;
    }

    NodoLibros* actual = cabeza;
    cout << "Mostrando libros:\n";
    do {
        cout << "T�tulo: " << actual->getTitulo()
             << ", Autor: " << actual->getAutor()
             << ", ISBN: " << actual->getIsbn()
             << ", G�nero: " << actual->getGenero()
             << ", A�o de Lanzamiento: " << actual->getAnioLanzamiento()
             << ", Precio: " << actual->getPrecio()
             << ", Calificaci�n: " << actual->getCalificacion() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaLibros::guardarEnArchivoJSON() {
    if (!cabeza) {
        cout << "La lista de libros est� vac�a. Nada que guardar.\n";
        return;
    }

    json jLibros = json::array();

    NodoLibros* actual = cabeza;
    do {
        jLibros.push_back({
            {"titulo", actual->getTitulo()},
            {"autor", actual->getAutor()},
            {"isbn", actual->getIsbn()},
            {"genero", actual->getGenero()},
            {"anioLanzamiento", actual->getAnioLanzamiento()},
            {"precio", actual->getPrecio()},
            {"calificacion", actual->getCalificacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::ofstream archivo("libros.json");
    if (archivo.is_open()) {
        archivo << jLibros.dump(4);
        archivo.close();
    //    cout << "Datos guardados correctamente en 'libros.json'.\n";
    } else {
        cout << "Error: No se pudo abrir el archivo para guardar datos.\n";
    }
}

void ListaLibros::cargarDesdeArchivoJSON() {
    std::ifstream archivo("libros.json");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo 'libros.json' para cargar datos.\n";
        return;
    }

    json jLibros;
    archivo >> jLibros; // Leer el contenido del archivo JSON
    archivo.close();

    for (const auto& libro : jLibros) {
        // Asegurarse de que los campos coincidan con el JSON
        string titulo = libro["titulo"];
        string autor = libro["autor"];
        string isbn = libro["isbn"];
        string genero = libro["genero"];
        string anioLanzamiento = libro["anioLanzamiento"];
        float precio = libro["precio"];
        float calificacion = libro["calificacion"];

        // Depuraci�n: Confirmar que los datos se est�n leyendo
        cout << "Cargando libro: T�tulo: " << titulo << ", Autor: " << autor
             << ", ISBN: " << isbn << ", G�nero: " << genero
             << ", A�o de Lanzamiento: " << anioLanzamiento
             << ", Precio: " << precio
             << ", Calificaci�n: " << calificacion << "\n";

        insertar(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
    }

    cout << "Datos cargados correctamente desde 'libros.json'.\n";
}


string ListaLibros::seleccionarAutor(ListaAutores& listaAutores) {
    cout << "Seleccione un autor de la lista:\n";
    listaAutores.mostrar();

    string cedula;
    cout << "Ingrese la c�dula del autor: ";
    cin >> cedula;

    NodoAutores* autor = listaAutores.buscar(cedula);
    if (autor) {
        return autor->getNombre() + " " + autor->getApellido();
    } else {
        cout << "Error: Autor no encontrado.\n";
        return "";
    }
}
