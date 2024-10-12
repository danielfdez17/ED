#include <iostream>
#include <iomanip>
#include <fstream>
#include "List.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    List<int>lista, aux;
    int x; cin >> x;
    while (x != 0) {
        lista.push_back(x);
        cin >> x;
    }
    cin >> x;
    while (x != 0) {
        aux.push_back(x);
        cin >> x;
    }
    lista.interseccion(aux);
    for (List<int>::ConstIterator it = lista.cbegin(); it != lista.cend(); it++) cout << it.elem() << " "; cout << "\n";
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