#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "Arbin.h"
using namespace std;

bool resolver(Arbin<int>const& arbol, int min, int max) {
    if (arbol.esVacio()) return true;
    if (arbol.raiz() <= min || arbol.raiz() >= max) return false;
    return resolver(arbol.hijoIz(), min, arbol.raiz()) && resolver(arbol.hijoDr(), arbol.raiz(), max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbol(-1);
    cout << (resolver(arbol, INT_MIN, INT_MAX) ? "SI\n" : "NO\n");
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
