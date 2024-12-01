#pragma once
#include "NodoLibro.h"
#include <string>

class ListaCircularDoble {
private:
    NodoLibro* cabeza;

    bool validarISBNUnico(std::string);

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    void insertar(std::string, std::string, int, std::string, std::string, std::string, double, double);
    NodoLibro* buscar(std::string);
    bool eliminar(std::string);
    void mostrar();
};
