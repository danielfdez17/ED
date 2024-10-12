#include <iostream>
#include <iomanip>
#include <fstream>
#include "dequeue.h"
using namespace std;

void lectura(Dequeue<int>& cola) {
    int n;
    //lectura de las dos colas dobles
    cin >> n;
    while (n != 0) {
        cola.push_back(n);
        cin >> n;
    }
}


void resuelveCaso() {
    Dequeue<int> principal, secundaria;
    //lectura de las dos colas dobles
    lectura(principal);
    lectura(secundaria);
    //llamada al método
    principal.unzip(secundaria);
    //escritura
    cout << principal << endl;
    cout << secundaria << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}