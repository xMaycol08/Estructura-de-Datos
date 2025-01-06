#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <vector>
#include <utility>

class Validaciones {
public:
    bool validarDimensiones(int n, int m);
    bool esEntradaValida(const std::string& entrada);
    std::string obtenerEntrada();
    std::vector<std::vector<int>> obtenerMatriz(int n, int m);
    std::pair<int, int> obtenerDimensiones();
private:
    bool esCaracterValido(char c, const std::string& entrada);
};

#endif // VALIDACIONES_H
