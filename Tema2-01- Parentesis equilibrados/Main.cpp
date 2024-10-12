#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

bool opened(char const&c) {
    return c == '(' || c == '[' || c == '{';
}
bool closed(char const&c) {
    return c == ')' || c == ']' || c == '}';
}
bool match(char const& o, char const& c) {
    return (o == '(' && c == ')') ||
        (o == '{' && c == '}') ||
        (o == '[' && c == ']');
}
// El coste en el caso peor es lineal en el s.size()
bool solve(string s) {
    stack<char>p;
    bool finish = false;
    int i = 0;
    while (i < s.size() && !finish) {
        char c = s[i];
        if (opened(c)) p.push(c);
        // Si c es cerrado y la pila esta vacia, se acaba la busqueda
        else if (closed(c))
            if (!p.empty() && match(p.top(), c)) p.pop();
            else finish = true;
        i++;
    }
    return finish ? false : p.empty();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string s; getline(cin, s);
    if (!cin) return false;
    cout << (solve(s) ? "SI\n" : "NO\n");
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