#pragma once
#include <string>

class NodoLibro {
private:
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    std::string isbn;
    std::string genero;
    std::string sinopsis;
    double precio;
    double calificacion;
    NodoLibro* siguiente;
    NodoLibro* anterior;

public:
    NodoLibro(std::string, std::string, int, std::string, std::string, std::string, double, double);
    // Getters y setters
    std::string getTitulo();
    std::string getAutor();
    int getAnioPublicacion();
    std::string getISBN();
    std::string getGenero();
    std::string getSinopsis();
    double getPrecio();
    double getCalificacion();

    void setTitulo(std::string);
    void setAutor(std::string);
    void setAnioPublicacion(int);
    void setISBN(std::string);
    void setGenero(std::string);
    void setSinopsis(std::string);
    void setPrecio(double);
    void setCalificacion(double);

    NodoLibro* getSiguiente();
    NodoLibro* getAnterior();
    void setSiguiente(NodoLibro*);
    void setAnterior(NodoLibro*);
};
