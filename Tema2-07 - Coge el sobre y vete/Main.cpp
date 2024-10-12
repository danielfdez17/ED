#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
using namespace std;
// función que resuelve el problema


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int s, k, aux; cin >> s >> k;
    if (s ==  0 && k == 0) return false;
    deque<int> sobres, mayores;
    for (int i = 0; i < k; ++i) {
        cin >> aux;
        sobres.push_back(aux);
        while (!mayores.empty() && (mayores.back() < aux)) mayores.pop_back();
        mayores.push_back(aux);
    }
    for (int i = k; i < s; ++i) {
        cout << mayores.front() << " ";
        cin >> aux;
        sobres.push_back(aux);
        if (mayores.front() == sobres.front()) { mayores.pop_front(); }
        sobres.pop_front();
        while (!mayores.empty() && (mayores.back() < aux)) { mayores.pop_back(); }
        mayores.push_back(aux);
    }
    cout << mayores.front() << '\n';
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