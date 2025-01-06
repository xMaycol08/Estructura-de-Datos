#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <utility>
#include <string> // Incluir string

// Clase para realizar validaciones
class Validaciones {
public:
    // Método para validar la entrada
    bool validarEntrada(int& N, int& M, std::vector<std::pair<int, int>>& intervalos);
    // Método para mostrar mensajes de error
    void mostrarMensajeError(int codigoError);
    // Método para leer y validar N y M
    bool leerYValidarNM(int& N, int& M);
    // Método para leer y validar intervalos
    bool leerYValidarIntervalos(int M, std::vector<std::pair<int, int>>& intervalos);
};

// Funcion para leer una linea filtrando caracteres no permitidos
std::string leerLineaFiltrada();

#endif // VALIDACIONES_H
