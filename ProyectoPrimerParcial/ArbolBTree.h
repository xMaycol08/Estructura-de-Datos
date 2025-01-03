#ifndef ARBOLBTREE_H
#define ARBOLBTREE_H

#include "NodoBTree.h"
#include "Libro.h"
#include <string>

class ArbolBTree {
private:
    NodoBTree* raiz;
    int t; // Grado mínimo
    std::string archivoLibros = "libros.txt";  // Archivo donde se guardarán los libros
    bool evitarGuardar = false;                // Bandera para controlar el guardado

    void insertarEnNodo(NodoBTree* nodo, const Libro& libro);
    NodoBTree* buscarEnNodo(NodoBTree* nodo, const std::string& isbn);

public:
    ArbolBTree(int t);
    void insertar(const Libro& libro);
    NodoBTree* buscarPorIsbn(const std::string& isbn);
    NodoBTree* buscar(const std::string& titulo);
    void eliminar(const std::string& titulo);
    void imprimirLibros();
    NodoBTree* buscarLibroPorIsbn(const std::string& isbn);
    Persona buscarAutorPorIsni(const std::string& isni);
    void guardarLibrosEnArchivo();
};

#endif // ARBOLBTREE_H
