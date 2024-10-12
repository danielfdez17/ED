#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    bool ok;
    int ceros;
};

tsol resolver(Arbin<int>const& arbol) {
    if (arbol.esVacio()) return { true, 0 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    bool ok = i.ok && d.ok && (abs(i.ceros - d.ceros) <= 1);
    int ceros = i.ceros + d.ceros;
    if (arbol.raiz() == 0) ceros++;
    return { ok, ceros };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbol(-1);
    tsol sol = resolver(arbol);
    cout << (sol.ok ? "SI\n" : "NO\n");
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