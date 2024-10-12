#include <iostream>               
#include <fstream>
#include "Arbin.h"
 //#include "Arbin_Smart.h" //Si lo prefieres puedes usar esta otra clase
#include <algorithm>
using namespace std;

struct tsol {
    int salvados;
    int hijos;
};

/**
 * Escribe la función que resuelve el problema. Puedes usar funciones auxiliares si lo
 * crees necesario.
 *
 * IMPORTANTE: - NO puedes usar parámetros que sean a la vez, entrada y salida
 *             - Indica el coste de tu función
 *
 */

// Coste: es lineal en el numero de elementos del arbol, ya que tiene que recorrer ambos hijos de la raiz para ver qué solución es mejor
tsol resolver(const Arbin<char>& arbol) {
    if (arbol.esVacio()) return { 0,0 };
    tsol i = resolver(arbol.hijoIz());
    tsol d = resolver(arbol.hijoDr());
    return { max(i.salvados + d.hijos, d.salvados + i.hijos),i.hijos + d.hijos + 1 };
}


void resuelveCaso() {
    Arbin<char> arbol = Arbin<char>::leerArbolInorden();
    //Llamada a la función y escritura de los datos
    tsol sol = resolver(arbol);
    cout << sol.salvados << "\n";
}


///
int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int casos;
    cin >> casos;
    while (casos--) {
        resuelveCaso();
    }
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
