#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    int nodos;
    int hojas;
    int altura;
};

// Recorrer el arbol una sola vez y sacar los tres valores
// El coste del algoritmo es lineal en el numero de elementos del arbol
tsol resolver(Arbin<char>const& arbol) {
    if (arbol.esVacio()) return { 0,0,0 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    int nodos = 1, hojas = 0, altura = 1;
    if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) hojas++;
    nodos += (i.nodos + d.nodos);
    hojas += (i.hojas + d.hojas);
    altura += max(i.altura, d.altura);
    return { nodos,hojas,altura };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<char>arbol = Arbin<char>::leerArbol('.');
    tsol sol = resolver(arbol);
    cout << sol.nodos << " " << sol.hojas << " " << sol.altura << "\n";
    //cout << arbol.nodos() << " " << arbol.hojas() << " " << arbol.altura() << "\n";
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