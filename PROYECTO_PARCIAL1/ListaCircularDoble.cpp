#include "ListaCircularDoble.h"
#include <iostream>

using namespace std;

ListaCircularDoble::ListaCircularDoble() : cabeza(nullptr) {}

ListaCircularDoble::~ListaCircularDoble() {
    if (!cabeza) return;

    NodoLibro* actual = cabeza;
    do {
        NodoLibro* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    } while (actual != cabeza);
    cabeza = nullptr;
}

bool ListaCircularDoble::validarISBNUnico(std::string isbn) {
    if (!cabeza) return true;

    NodoLibro* actual = cabeza;
    do {
        if (actual->getISBN() == isbn) return false;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return true;
}

void ListaCircularDoble::insertar(std::string titulo, std::string autor, int anioPublicacion,
                                  std::string isbn, std::string genero, std::string sinopsis,
                                  double precio, double calificacion) {
    if (!validarISBNUnico(isbn)) {
        cout << "Error: ISBN ya existe en la lista.\n";
        return;
    }

    NodoLibro* nuevo = new NodoLibro(titulo, autor, anioPublicacion, isbn, genero, sinopsis, precio, calificacion);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        NodoLibro* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    cout << "Libro agregado correctamente.\n";
}

NodoLibro* ListaCircularDoble::buscar(std::string isbn) {
    if (!cabeza) return nullptr;

    NodoLibro* actual = cabeza;
    do {
        if (actual->getISBN() == isbn) return actual;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
}

bool ListaCircularDoble::eliminar(std::string isbn) {
    NodoLibro* aEliminar = buscar(isbn);
    if (!aEliminar) {
        cout << "Error: Libro no encontrado.\n";
        return false;
    }

    if (aEliminar->getSiguiente() == aEliminar) {
        delete aEliminar;
        cabeza = nullptr;
    } else {
        NodoLibro* anterior = aEliminar->getAnterior();
        NodoLibro* siguiente = aEliminar->getSiguiente();

        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);

        if (aEliminar == cabeza) cabeza = siguiente;
        delete aEliminar;
    }

    cout << "Libro eliminado correctamente.\n";
    return true;
}

void ListaCircularDoble::mostrar() {
    if (!cabeza) {
        cout << "Lista vacia.\n";
        return;
    }

    NodoLibro* actual = cabeza;
    do {
        cout << "Titulo: " << actual->getTitulo() << ", Autor: " << actual->getAutor()
             << ", Año: " << actual->getAnioPublicacion() << ", ISBN: " << actual->getISBN()
             << ", Genero: " << actual->getGenero() << ", Precio: $" << actual->getPrecio()
             << ", Calificacion: " << actual->getCalificacion() << "/5\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}
