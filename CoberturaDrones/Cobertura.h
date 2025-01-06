#ifndef COBERTURA_H
#define COBERTURA_H

#include <vector>

class Cobertura {
public:
    // Calcular el radio minimo requerido para cubrir todas las areas
    int calcularRadioMinimo(int n, int m, const std::vector<int>& areas, const std::vector<int>& drones);
};

#endif // COBERTURA_H
