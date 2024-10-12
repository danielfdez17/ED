#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

// El coste del algoritmo es lineal en el numero de elemntos del arbol
// equipos, atrapados
pair<int, int> resolver(Arbin<int>const& arbol) {
    if (arbol.esVacio()) return { 0,0 };
    pair<int, int>i = resolver(arbol.hijoIz());
    pair<int, int>d = resolver(arbol.hijoDr());
    // Si hay excursionistas atrapados en los hijos
    if (i.second > 0 || d.second > 0) return { i.first + d.first, arbol.raiz() + max(i.second,d.second) };
    // Si hay excursionistas en la raiz
    if (arbol.raiz() != 0) return { 1,arbol.raiz() };
    return{ 0,0 };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbol(-1);
    pair<int, int>p = resolver(arbol);
    cout << p.first << " " << p.second << "\n";
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