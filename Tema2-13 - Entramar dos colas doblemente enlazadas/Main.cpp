#include <iostream>
#include <iomanip>
#include <fstream>
#include "dequeue.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
// EL ENUNCIADO ES PARA List<T>, PERO EL JUEZ ESTABA PREPARADO PARA QUE SEAN Dequeue<T>
void resuelveCaso() {
    int n; cin >> n;
    Dequeue<int>lista, other;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        lista.push_back(x);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        other.push_back(x);
    }
    lista.zip(other);
    int cont = 0;
    lista.display(); cout << "\n";
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