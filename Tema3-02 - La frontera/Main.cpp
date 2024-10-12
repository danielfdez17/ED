#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Arbin.h"
using namespace std;

// El coste del algoritmo es lineal en el numero de elementos del arbol
void resolver(Arbin<int>const& arbol, vector<int>&v) {
    if (arbol.esVacio()) return;
    if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) v.push_back(arbol.raiz());
    resolver(arbol.hijoIz(), v);
    resolver(arbol.hijoDr(), v);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int> arbol = Arbin<int>::leerArbol(-1);
    vector<int>v;
    resolver(arbol, v);
    for (int& i : v) {
        cout << i << " ";
    }
    cout << "\n";
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