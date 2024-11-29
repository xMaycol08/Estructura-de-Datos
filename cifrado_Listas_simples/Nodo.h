/***********************************************************************
 * Module:  Nodo.h
 * Author:  Maycol Celi
 * Date: 28/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <string>
using namespace std;

class Nodo {
private:
    string cedula;
    string nombre;
    string apellido;
    Nodo* siguiente;

public:
    Nodo(string cedula, string nombre, string apellido);
    string getCedula();
    string getNombre();
    string getApellido();
    void setNombre(string nuevoNombre);
    void setApellido(string nuevoApellido);
    Nodo* getSiguiente();
    void setSiguiente(Nodo* nuevoSiguiente);

    friend class ListaSimple;
};
