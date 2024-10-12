#include <iostream>
#include <iomanip>
#include <fstream>
#include "Hora.h"
#include<vector>
using namespace std;
// Al utilizar el algoritmo de busqueda binaria, el coste del mismo pertenece a O(log(v.size())) en el caso peor (esta en un extremo)
// En el caso mejor es constante porque entra directamente en los CB o es el elemento del medio
void buscar_hora(vector<Hora>const&v, Hora const&h, Hora&sol, bool&encontrado, int c, int f) {
    if (encontrado) return;
    if (c == f) { // CB: un elemento
        if (h < v[c] || h == v[c]) {
            encontrado = true;
            sol = v[c];
        }
    }
    else if (c == f - 1) { // CB: dos elementos
        if (h < v[c] || h == v[c]) {
            encontrado = true;
            sol = v[c];
        }
        else if (h < v[f] || h == v[f]) {
            encontrado = true;
            sol = v[f];
        }
    }
    else { // CR
        int m = (c + f) / 2;
        if (v[m] == h) {
            encontrado = true;
            sol = h;
        }
        else if (h < v[m]) buscar_hora(v,h,sol,encontrado,c,m);
        else buscar_hora(v,h,sol,encontrado,m+1,f);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int trenes, horas; cin >> trenes >> horas;
    if (trenes == 0 && horas == 0) return false;
    vector<Hora>v(trenes);
    for (Hora&h : v) cin >> h;
        for (int i = 0; i < horas; i++) {
        try {
            Hora h, sol; cin >> h;
            bool encontrado = false;
            buscar_hora(v,h,sol,encontrado,0,trenes-1);
            if (encontrado) cout << sol << "\n";
            else cout << "NO\n";
        } catch (Error e) { cout << e.getMsg() << "\n"; }
    }
    cout << "---\n";
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
