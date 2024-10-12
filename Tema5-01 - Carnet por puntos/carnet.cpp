#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include<unordered_map>
using namespace std;

const int MAX_PUNTOS = 15;

class carnet_puntos 
private:
    unordered_map<string, int>conductores; // Mapa de conductores con sus respectivos puntos
    vector<int>puntos; // Guarda las personas con x puntos que hay en el mapa (x pertenece a [0, MAX_PUNTOS])
public:
    // Constructor vacio para el vector
    carnet_puntos(): puntos(MAX_PUNTOS + 1, 0) {}
    // COSTE: constante, ya que las operaciones find() e insert() son constantes (stl), y el acceso al vector tambien es constante
    void nuevo(string dni) {
        unordered_map<string, int>::iterator it = conductores.find(dni);
        if (it != conductores.end()) throw domain_error("Conductor duplicado");
        conductores.insert({ dni, MAX_PUNTOS });
        puntos[MAX_PUNTOS]++;
    }
    // COSTE: constante, ya que la operacion find() es constante (stl) y los accesos al valor de la clave 'dni' y al vector de puntos son constantes
    void quitar(string dni, int punt) {
        unordered_map<string, int>::iterator it = conductores.find(dni);
        if (it == conductores.end()) throw domain_error("Conductor inexistente");
        puntos[it->second]--;
        if (punt > it->second) it->second = 0;
        else it->second -= punt;
        puntos[it->second]++;
    }
    // COSTE: constante, ya que la operacion find() es constante
    int consultar(string dni) {
        unordered_map<string, int>::iterator it = conductores.find(dni);
        if (it == conductores.end()) throw domain_error("Conductor inexistente");
        return it->second;
    }
    // COSTE: constante, ya que el acceso al vector es constante
    int cuantos_con_puntos(int punt) {
        if (punt < 0 || punt > MAX_PUNTOS) throw domain_error("Puntos no validos");
        return puntos[punt];
    }

;

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
