/***********************************************************************
 * Module:  multiple.cpp
 * Author:  Maycol Celi
 * Date: 13/11/2024
 * Purpose: Secuencia de Golomb
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include <iostream>
using namespace std;

int golomb(int n) {
    if (n == 1) return 1; 
    return 1 + golomb(n - golomb(golomb(n - 1)));
}

int main() {
    int n;
    cout << "Ingresa un número para calcular la secuencia de Golomb: ";
    cin >> n;
    cout << "Golomb(" << n << ") = " << golomb(n) << endl;
    return 0;
}
