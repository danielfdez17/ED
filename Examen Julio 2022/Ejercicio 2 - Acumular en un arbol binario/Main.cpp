#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

Arbin<int> resolver(Arbin<int>const& arbol) {
    if (arbol.esVacio()) return Arbin<int>(); // Arbol vacio
    if (arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) return Arbin<int>(arbol.raiz()); // Hoja
    Arbin<int>i = resolver(arbol.hijoIz());
    Arbin<int>d = resolver(arbol.hijoDr());
    int raiz = arbol.raiz();
    if (!i.esVacio()) raiz += i.raiz();
    if (!d.esVacio()) raiz += d.raiz();
    return Arbin<int>(i, raiz, d);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbolInorden();
    cout << resolver(arbol) << "\n";
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