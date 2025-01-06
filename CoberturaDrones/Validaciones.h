#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <string>
#include <stdexcept>

class Validaciones {
public:
    // Validar los valores de entrada
    bool validarEntradas(int n, int m, const std::vector<int>& areas, const std::vector<int>& drones);

    // Mostrar mensaje de entrada
    void mensajeEntrada(const std::string& tipo);

    // Mostrar mensaje de salida
    void mensajeSalida(int radioMinimo);

    // Validar y filtrar caracteres de entrada
    static void filtrarEntrada(std::string& input, int maxNumeros);

    // Validar que se ingresen exactamente dos números
    static bool validarDosNumeros(const std::string& input, int& n, int& m);
};

#endif // VALIDACIONES_H
