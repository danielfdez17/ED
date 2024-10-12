#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

struct tsol {
    bool zurdo;
    int hijos;
};

// El coste del algoritmo es lineal en el numero de elementos del arbol
tsol resolver(Arbin<char>const& arbol) {
    if (arbol.esVacio()) return { true, 0 };
    if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) return { true,1 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    int hijos = 0;
    if (arbol.raiz() == '*') hijos++;
    return { i.zurdo && d.zurdo && (i.hijos > d.hijos) , i.hijos + d.hijos + hijos };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<char>arbol = Arbin<char>::leerArbolInorden();
    //cout << arbol << "\n";
    tsol sol = resolver(arbol);
    cout << (sol.zurdo ? "SI\n" : "NO\n");
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