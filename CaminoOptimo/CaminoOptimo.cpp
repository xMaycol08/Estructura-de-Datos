#include "CaminoOptimo.h"
#include <algorithm>
#include <vector>
#include <climits> // Incluir este encabezado para INT_MAX
#include <iostream>
#include <functional> // Include this header for std::function

int CaminoOptimo::calcularCostoMinimo(const std::vector<std::vector<int>>& grid, int n, int m) {
    try {
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MAX));

        // Inicializar el costo de la celda inicial
        dp[0][0] = grid[0][0];

        // Calcular los costos mínimos usando programación dinámica
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + grid[i][j]);
                }
                if (j > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + grid[i][j]);
                }
            }
        }

        return dp[n - 1][m - 1];
    } catch (const std::exception& e) {
        std::cerr << "Error calculando costo minimo: " << e.what() << std::endl;
        return INT_MAX;
    } catch (...) {
        std::cerr << "Error desconocido calculando costo minimo." << std::endl;
        return INT_MAX;
    }
}
