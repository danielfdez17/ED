#include <iostream>
#include <iomanip>
#include <fstream>
#include "Horas.h"
#include "list_linked_single_plus.h"
using namespace std;

// función que resuelve el problema
istream& operator>>(istream& CIN, horas& h) {
    int hours, minutes, seconds;
    char aux;
    CIN >> hours >> aux >> minutes >> aux >> seconds;
    h = horas(hours, minutes, seconds);
    return CIN;
}

ostream& operator<<(ostream& COUT, horas& h) {
    if (h.getHours() < 10) {
        COUT << "0";
    }
    COUT << h.getHours() << ":";
    if (h.getMinutes() < 10) {
        COUT << "0";
    }
    COUT << h.getMinutes() << ":";
    if (h.getSeconds() < 10) {
        COUT << "0";
    }
    COUT << h.getSeconds();
    return COUT;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;
    ListLinkedSingle<horas>lista;
    horas aux;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        lista.push_back(aux);
    }
    lista.eliminarPares();
    lista.display();
    cout << "\n";
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
