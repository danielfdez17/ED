#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int x; cin >> x;
    Queue<int>q, colegas;
    while (x != -1) {
        q.push_back(x);
        cin >> x;
    }
    int pringao; cin >> pringao;
    cin >> x;
    while (x != -1) {
        colegas.push_back(x);
        cin >> x;
    }
    cout << q << "\n";
    q.cuela(pringao, colegas);
    cout << q << "\n";
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