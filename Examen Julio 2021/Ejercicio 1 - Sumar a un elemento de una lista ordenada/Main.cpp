#include <iostream>
#include <iomanip>
#include <fstream>
#include "List.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, pos, m; cin >> n >> pos >> m;
    if (n == 0 && pos == 0 && m == 0) return false;
    List<int>lista;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        lista.push_back(x);
    }
    lista.add_to(pos, m);
    cout << "[";
    int cont = 0;
    for (List<int>::ConstIterator it = lista.cbegin(); it != lista.cend(); it++) {
        cout << it.elem();
        if (cont + 1 != lista.size()) cout << ", ";
        cont++;
    }
    cout << "]\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


        while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}