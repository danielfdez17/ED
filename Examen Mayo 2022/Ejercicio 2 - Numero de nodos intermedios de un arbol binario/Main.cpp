#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    int nodos_intermedios;
    int hijos;
};

tsol resolver(Arbin<int>const& arbol, int padre) {
    if (arbol.esVacio()) return { 0,0 };
    tsol i = resolver(arbol.hijoIz(), arbol.raiz());
    tsol d = resolver(arbol.hijoDr(), arbol.raiz());
    int hijos = i.hijos + d.hijos + arbol.raiz(), nodos_intermedios = i.nodos_intermedios + d.nodos_intermedios;
    if (padre != 0 && arbol.raiz() == (std::abs(i.hijos - d.hijos) % padre)) nodos_intermedios++;
    return { nodos_intermedios, hijos};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<int>arbol = Arbin<int>::leerArbolInorden();
    cout << resolver(arbol, 0).nodos_intermedios << "\n";
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
