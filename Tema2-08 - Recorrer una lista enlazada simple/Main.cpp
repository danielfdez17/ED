#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "list_linked_single_plus.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    char c; cin >> c;
    if (!cin) return false;
    ListLinkedSingle<string>lista;
    string s;
    getline(cin, s);
    getline(cin, s);
    stringstream ss(s);
    int size = 0;
    while (ss) {
        string aux; ss >> aux;
        lista.push_back(aux);
        size++;
    }
    lista.mostrar(c);
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