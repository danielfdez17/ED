#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
using namespace std;

template <typename T>
// El coste del algoritmo es lineal en el numero de elementos del arbol
T resolver(Arbin<T>const& arbol) {
    if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) return arbol.raiz();
    T i, d;
    // Se llama a la funcion si el subarbol no es vacio
    if (!arbol.hijoIz().esVacio()) i = resolver(arbol.hijoIz()); 
    if (!arbol.hijoDr().esVacio()) d = resolver(arbol.hijoDr());
    if (arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) return arbol.raiz();
    // Hijo derecho vacio
    if (arbol.hijoDr().esVacio() && !arbol.hijoIz().esVacio()) return min(arbol.raiz(), i);
    // Hijo izquierdo vacio
    if (!arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) return min(arbol.raiz(), d);
    // Ninguno vacio
    return min(arbol.raiz(), min(i, d));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    char tipo; cin >> tipo;
    if (!cin) return false;
    if (tipo == 'N') {
        Arbin<int>arbol = Arbin<int>::leerArbolInorden();
        cout << resolver(arbol) << "\n";
    }
    else if (tipo == 'P') {
        Arbin<string>arbol = Arbin<string>::leerArbolInorden();
        cout << resolver(arbol) << "\n";
    }
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}