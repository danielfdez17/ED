#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    int caudal;
    int tramos;
};

// El coste del algoritmo es lineal en el numero de elementos del arbol
tsol resolver(Arbin<int>const& arbol) {
    if (arbol.esVacio()) return { 0,0 };
    if (arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) return { 1,0 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    int caudal = i.caudal + d.caudal - arbol.raiz();
    if (caudal < 0) caudal = 0;
    if (i.caudal >= 3) i.tramos++;
    if (d.caudal >= 3) d.tramos++;
    return { caudal,i.tramos + d.tramos };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbol(-1);
    cout << resolver(arbol).tramos << "\n";
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