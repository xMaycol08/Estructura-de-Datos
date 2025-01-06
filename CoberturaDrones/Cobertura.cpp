#include "Cobertura.h"
#include <algorithm>

// Calcular el radio minimo requerido para cubrir todas las areas
int Cobertura::calcularRadioMinimo(int n, int m, const std::vector<int>& areas, const std::vector<int>& drones) {
    int left = 0, right = 1000000000, result = right;

    // Busqueda binaria para el radio minimo
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int j = 0;
        bool covered = true;

        // Verificar si todas las areas estan cubiertas con el radio actual
        for (int i = 0; i < n; ++i) {
            while (j < m && drones[j] + mid < areas[i]) {
                ++j;
            }
            if (j == m || drones[j] - mid > areas[i]) {
                covered = false;
                break;
            }
        }

        // Ajustar el rango de busqueda basado en la cobertura
        if (covered) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}
