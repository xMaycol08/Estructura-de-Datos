#include "NodoLibro.h"

NodoLibro::NodoLibro(std::string _titulo, std::string _autor, int _anioPublicacion,
                     std::string _isbn, std::string _genero, std::string _sinopsis,
                     double _precio, double _calificacion)
    : titulo(_titulo), autor(_autor), anioPublicacion(_anioPublicacion),
      isbn(_isbn), genero(_genero), sinopsis(_sinopsis),
      precio(_precio), calificacion(_calificacion),
      siguiente(nullptr), anterior(nullptr) {}

// Getters
std::string NodoLibro::getTitulo() { return titulo; }
std::string NodoLibro::getAutor() { return autor; }
int NodoLibro::getAnioPublicacion() { return anioPublicacion; }
std::string NodoLibro::getISBN() { return isbn; }
std::string NodoLibro::getGenero() { return genero; }
std::string NodoLibro::getSinopsis() { return sinopsis; }
double NodoLibro::getPrecio() { return precio; }
double NodoLibro::getCalificacion() { return calificacion; }

// Setters
void NodoLibro::setTitulo(std::string _titulo) { titulo = _titulo; }
void NodoLibro::setAutor(std::string _autor) { autor = _autor; }
void NodoLibro::setAnioPublicacion(int _anio) { anioPublicacion = _anio; }
void NodoLibro::setISBN(std::string _isbn) { isbn = _isbn; }
void NodoLibro::setGenero(std::string _genero) { genero = _genero; }
void NodoLibro::setSinopsis(std::string _sinopsis) { sinopsis = _sinopsis; }
void NodoLibro::setPrecio(double _precio) { precio = _precio; }
void NodoLibro::setCalificacion(double _calificacion) { calificacion = _calificacion; }

// Punteros
NodoLibro* NodoLibro::getSiguiente() { return siguiente; }
NodoLibro* NodoLibro::getAnterior() { return anterior; }
void NodoLibro::setSiguiente(NodoLibro* nodo) { siguiente = nodo; }
void NodoLibro::setAnterior(NodoLibro* nodo) { anterior = nodo; }
