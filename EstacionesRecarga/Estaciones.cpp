#include "Estaciones.h"
#include <functional>

// Constructor
Estaciones::Estaciones(int N, const std::vector<std::pair<int, int>>& intervalos) : N(N), intervalos(intervalos) {
    // Ordenar los intervalos
    std::sort(this->intervalos.begin(), this->intervalos.end());
}

// Método para calcular la distancia máxima
int Estaciones::calcularDistanciaMaxima() {
    int izquierda = 0, derecha = intervalos.back().second - intervalos.front().first;
    int mejorDistancia = 0;

    // Lambda recursiva para buscar la mejor distancia
    std::function<void(int, int)> buscarMejorDistancia = [&](int izq, int der) {
        if (izq > der) return;
        int mitad = izq + (der - izq) / 2;
        if (esPosible(mitad)) {
            mejorDistancia = mitad;
            buscarMejorDistancia(mitad + 1, der);
        } else {
            buscarMejorDistancia(izq, mitad - 1);
        }
    };

    // Iniciar la búsqueda
    buscarMejorDistancia(izquierda, derecha);
    return mejorDistancia;
}

// Método para verificar si es posible una distancia dada
bool Estaciones::esPosible(int distancia) {
    int count = 1;
    int ultimaPosicion = intervalos[0].first;

    // Verificar cada intervalo
    for (const auto& intervalo : intervalos) {
        while (ultimaPosicion + distancia <= intervalo.second) {
            ultimaPosicion += distancia;
            count++;
            if (count >= N) return true;
        }
        ultimaPosicion = std::max(ultimaPosicion, intervalo.first);
    }

    return count >= N;
}
