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

bool ListaLibros::insertar(string titulo, string autor, string isbn, string anioLanzamiento, string genero, float precio, float calificacion) {
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
        cout << "La lista de libros está vacía.\n";
        return nullptr;
    }

    NodoLibros* actual = cabeza;
    do {
        // Depuración: Mostrar qué ISBN se compara
        cout << "Comparando ISBN en nodo: " << actual->getIsbn() << " con " << isbn << "\n";
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
    // Verificar si la lista está vacía
    if (!cabeza) {
        cout << "Error: La lista de libros está vacía.\n";
        return false;
    }

    NodoLibros* encontrado = buscar(isbn); // Buscar el nodo a eliminar
    if (!encontrado) {
        cout << "Error: Libro con ISBN " << isbn << " no encontrado.\n";
        return false;
    }

    // Caso: Único nodo en la lista
    if (encontrado->getSiguiente() == encontrado) {
        cabeza = nullptr;
    } else {
        // Caso: Múltiples nodos en la lista
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
        cout << "Lista de libros vacía.\n";
        return;
    }

    NodoLibros* actual = cabeza;
    cout << "Mostrando libros:\n";
    do {
        cout << "Título: " << actual->getTitulo()
             << ", Autor: " << actual->getAutor()
             << ", ISBN: " << actual->getIsbn()
             << ", Género: " << actual->getGenero()
             << ", Año de Lanzamiento: " << actual->getAnioLanzamiento()
             << ", Precio: " << actual->getPrecio()
             << ", Calificación: " << actual->getCalificacion() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaLibros::guardarEnArchivoJSON() {
    if (!cabeza) {
        cout << "La lista de libros está vacía. Nada que guardar.\n";
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
        cout << "Datos guardados correctamente en 'libros.json'.\n";
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

        // Depuración: Confirmar que los datos se están leyendo
        cout << "Cargando libro: Título: " << titulo << ", Autor: " << autor 
             << ", ISBN: " << isbn << ", Género: " << genero 
             << ", Año de Lanzamiento: " << anioLanzamiento 
             << ", Precio: " << precio 
             << ", Calificación: " << calificacion << "\n";

        insertar(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
    }

    cout << "Datos cargados correctamente desde 'libros.json'.\n";
}


string ListaLibros::seleccionarAutor(ListaAutores& listaAutores) {
    cout << "Seleccione un autor de la lista:\n";
    listaAutores.mostrar();

    string cedula;
    cout << "Ingrese la cédula del autor: ";
    cin >> cedula;

    NodoAutores* autor = listaAutores.buscar(cedula);
    if (autor) {
        return autor->getNombre() + " " + autor->getApellido();
    } else {
        cout << "Error: Autor no encontrado.\n";
        return "";
    }
}