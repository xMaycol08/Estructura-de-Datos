#ifndef ESTACIONES_H
#define ESTACIONES_H

#include <vector>
#include <algorithm>
#include <functional> // Incluir funcional

// Clase para manejar las estaciones
class Estaciones {
public:
    // Constructor
    Estaciones(int N, const std::vector<std::pair<int, int>>& intervalos);
    // Método para calcular la distancia máxima
    int calcularDistanciaMaxima();

private:
    int N; // Número de estaciones
    std::vector<std::pair<int, int>> intervalos; // Intervalos de estaciones
    // Método para verificar si es posible una distancia dada
    bool esPosible(int distancia);
};

#endif // ESTACIONES_H
