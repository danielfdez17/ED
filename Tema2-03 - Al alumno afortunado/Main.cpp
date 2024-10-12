#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, salto; cin >> n >> salto;
    if (n == 0 && salto == 0) return false;
    queue<int>q;
    for (int i = 1; i <= n; i++) q.push(i);
    int cont = 0;
    while (q.size() != 1) {
        int aux = q.front();
            q.pop();
        if (cont == salto) {
            cont = 0;
        }
        else {
            q.push(aux);
            cont++;
        }
    }
    cout << q.front() << "\n";
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
