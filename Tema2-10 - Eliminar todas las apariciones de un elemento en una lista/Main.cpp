#include <iostream>
#include <iomanip>
#include <fstream>
#include "List.h"
using namespace std;

void mostrar(ostream& COUT, const List<int>& l) {
    List<int>::ConstIterator it = l.cbegin();
    while (it != l.cend()) {
        COUT << *it << " ";
        ++it;
    }
    COUT << "\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    List<int> lista;
    int x;
    cin >> x;
    while (x != -1) {
        lista.push_back(x);
        cin >> x;
    }
    cin >> x;

    mostrar(cout, lista);
    lista.eliminar_elemento(x);
    mostrar(cout, lista);

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