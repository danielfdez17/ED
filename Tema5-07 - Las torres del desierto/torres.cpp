#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <list>
using namespace std;

#include "torres.h"

bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    string nombre; int x, y; Direccion dir;
    Desierto d;
    while (operacion != "FIN") {
        try {
            if (operacion == "anyadir_torre") {
                cin >> nombre >> x >> y;
                d.anyadir_torre(nombre, x, y);
            }
            else if (operacion == "eliminar_torre") {
                cin >> nombre;
                d.eliminar_torre(nombre);
            }
            else if (operacion == "posicion") {
                cin >> nombre;
                pair<int, int>p = d.posicion(nombre);
                cout << p.first << " " << p.second << "\n";
            }
            else if (operacion == "torre_en_posicion") {
                cin >> x >> y;
                pair<bool, string>p = d.torre_en_posicion(x, y);
                cout << (p.first ? "SI " + p.second : "NO") << "\n";
            }
            else if (operacion == "torre_mas_cercana") {
                cin >> nombre >> dir;
                string s = d.torre_mas_cercana(nombre, dir);
                cout << s << "\n";
            }
            else { // operacion desconocida
                assert(false);
            }
        }
        catch (domain_error e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelve());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
