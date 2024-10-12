#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    string lider;
    int enanos;
};
// El coste es lineal para todos los casos, ya que se recorren todos los nodos del arbol
tsol resolver(Arbin<string>const& arbol) {
    if (arbol.esVacio()) return { "",0 };
    if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) return { arbol.raiz(), 1 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    string lider; int enanos;
    if (i.enanos == d.enanos) lider = min(i.lider, d.lider);
    else lider = (i.enanos > d.enanos) ? i.lider : d.lider;
    if (arbol.raiz() == "Orcos") {
        enanos = (i.enanos + d.enanos) / 2;
    }
    else enanos = i.enanos + d.enanos;
    return { lider, enanos };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<string>arbol = Arbin<string>::leerArbol(".");
    tsol sol = resolver(arbol);
    if (sol.enanos == 0) cout << "Ninguno\n";
    else cout << sol.lider << " " << sol.enanos << "\n";
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