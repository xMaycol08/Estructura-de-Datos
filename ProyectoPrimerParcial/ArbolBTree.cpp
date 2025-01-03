#include "ArbolBTree.h"
#include "Persona.h"
#include <iostream>
#include <fstream>
#include <functional>

ArbolBTree::ArbolBTree(int t) : raiz(nullptr), t(t) {
    // Inicialización del árbol
}

void ArbolBTree::insertar(const Libro& libro) {
    if (raiz == nullptr) {
        raiz = new NodoBTree(true);
        raiz->claves.push_back(libro);
    } else {
        insertarEnNodo(raiz, libro);
    }
    std::cout << "Libro agregado: " << libro.getTitulo() << std::endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        guardarLibrosEnArchivo();
    }
}

void ArbolBTree::insertarEnNodo(NodoBTree* /*nodo*/, const Libro& /*libro*/) {
    // Implementación pendiente
}

NodoBTree* ArbolBTree::buscar(const std::string& /*titulo*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarPorIsbn(const std::string& /*isbn*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarEnNodo(NodoBTree* /*nodo*/, const std::string& /*isbn*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarLibroPorIsbn(const std::string& isbn) {
    if (!raiz) return nullptr;
    NodoBTree* actual = raiz;
    while (actual) {
        for (const auto& libro : actual->claves) {
            if (libro.getIsbn() == isbn) {
                return actual;
            }
        }
        // Move to the next node based on the B-Tree properties
        // This part depends on the specific implementation of your B-Tree
        // ...existing code for moving to the next node...
    }
    return nullptr;
}

Persona ArbolBTree::buscarAutorPorIsni(const std::string& isni) {
    if (!raiz) return Persona();
    NodoBTree* actual = raiz;
    while (actual) {
        for (const auto& libro : actual->claves) {
            if (libro.getAutor().getIsni() == isni) {
                return libro.getAutor();
            }
        }
        // Move to the next node based on the B-Tree properties
        // This part depends on the specific implementation of your B-Tree
        // ...existing code for moving to the next node...
    }
    return Persona();
}

void ArbolBTree::guardarLibrosEnArchivo() {
    std::ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    // Helper function to traverse the B-Tree and save books
    std::function<void(NodoBTree*)> guardarNodo = [&](NodoBTree* nodo) {
        if (nodo) {
            for (const auto& libro : nodo->claves) {
                archivo << libro.getTitulo() << ";"
                        << libro.getAutor().getNombre() << ";"
                        << libro.getAutor().getIsni() << ";"
                        << libro.getAutor().getFechaNacimiento().mostrar() << ";"
                        << libro.getIsbn() << ";"
                        << libro.getFechaPublicacion().mostrar() << std::endl;
            }
            for (auto hijo : nodo->hijos) {
                guardarNodo(hijo);
            }
        }
    };

    guardarNodo(raiz);

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        std::cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0) {
        // Si el archivo no se puede eliminar, mostrar error
        std::cout << "Error al eliminar el archivo de destino: " << archivoLibros << std::endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        // Mostrar error si renombrar falla
        perror("Error al renombrar el archivo temporal");
    } else {
        std::cout << "Libros guardados en el archivo: " << archivoLibros << std::endl;
    }
}

void ArbolBTree::eliminar(const std::string& /*titulo*/) {
    // Implementación pendiente
}

void ArbolBTree::imprimirLibros() {
    // Implementación pendiente
}
