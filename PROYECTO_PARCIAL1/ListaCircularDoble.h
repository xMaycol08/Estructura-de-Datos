#pragma once
#include "NodoLibro.h"
#include <string>

class ListaCircularDoble {
private:
    NodoLibro* cabeza;

    // M�todo privado para validar si un ISBN es �nico en la lista
    bool validarISBNUnico(std::string);

public:
    ListaCircularDoble();  // Constructor
    ~ListaCircularDoble(); // Destructor

    // M�todos p�blicos para manipular la lista
    void insertar(std::string, std::string, int, std::string, std::string, std::string, double, double);
    NodoLibro* buscar(std::string);
    bool eliminar(std::string);
    void mostrar();

    // M�todo p�blico para acceder al primer nodo de la lista
    NodoLibro* getCabeza() const {
        return cabeza;
    }
};
