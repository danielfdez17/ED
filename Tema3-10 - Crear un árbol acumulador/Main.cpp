#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

Arbin<int> acumula(Arbin<int>const& arbol) {
    if (arbol.esVacio()) return Arbin<int>();
    Arbin<int>i = acumula(arbol.hijoIz());
    Arbin<int>d = acumula(arbol.hijoDr());
    int elem = arbol.raiz();
    if (!i.esVacio()) elem += i.raiz();
    if (!d.esVacio()) elem += d.raiz();
    return Arbin<int>(i, elem, d);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbol(-1);
    List<int>* lista = acumula(arbol).preorden();
    for (auto it = lista->cbegin(); it != lista->cend(); it++) cout << it.elem() << " "; cout << "\n";
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