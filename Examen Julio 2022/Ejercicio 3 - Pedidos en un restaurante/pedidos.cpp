#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <list>
#include <queue>
#include "List.h"
using namespace std;

class restaurante {
private:
    list<pair<int, string>>cocina; // lista de pares mesa,plato que simula la cola de la cocina
    unordered_map<int, map<string, int>>mesas; // para cada mesa, los platos que han pedido y la cantidad de ellos
public:
    // Coste lineal en el caso peor, cons
    void nueva_mesa(int num) {
        // Constante de media, lineal en mesas.size() en el caso peor
        if (mesas.count(num) == 1) throw domain_error("Mesa ocupada");
        // Constante de media, lineal en mesas.size() en el caso peor
        mesas.insert({ num,{} });
    }
    // Coste lineal en el caso peor, logaritmico en el caso general
    void nuevo_pedido(int mesa, const string& plato) {
        // Constante de media, lineal en mesas.size() en el caso peor
        unordered_map<int, map<string, int>>::iterator itMesas = mesas.find(mesa);
        if (itMesas == mesas.end()) throw domain_error("Mesa vacia");
        // Logaritmico en itMesas->second.size() (el numero de platos que haya pedido la mesa)
        map<string, int>::iterator itPlatos = itMesas->second.find(plato);
        // Si el plato no lo habian pedido, se inserta en el mapa
        if (itPlatos == itMesas->second.end()) itMesas->second.insert({ plato, 1 });
        // Si ya lo habian pedido, se incrementa el numero de veces que la mesa a pedido ese plato
        else itPlatos->second++;
        // Constante, simplemente se anyade al final
        cocina.push_back({ mesa,plato });
    }
    // Coste lineal en cualquier caso, ya que hay que recorrese la lista cocina entera para saber el ultimo plato de la mesa
    void cancelar_pedido(int mesa, const string& plato) {
        // Constante de media, lineal en mesas.size() en el caso peor
        unordered_map<int, map<string, int>>::iterator itMesas = mesas.find(mesa);
        if (itMesas == mesas.end()) throw domain_error("Mesa vacia");
        list<pair<int, string>>::iterator it = cocina.begin(), itAux;
        bool found = false;
        // Lineal en cocina.size(), no se puede hacer erase sobre un reverse_iterator, y tampoco se puede castear un reverse_iterator a un iterator
        while (it != cocina.end()) {
            if (it->first == mesa && it->second == plato) {
                itAux = it; found = true;
            }
            it++;
        }
        if (!found) throw domain_error("Producto no pedido por la mesa");
        // Logaritmico en itMesas->second.size() (numero de platos distintos pedidos por la mesa cocina.front().first)
        map<string, int>::iterator itPlatos = itMesas->second.find(cocina.front().second);
        // Constante amortizado (al pasarle un iterador)
        if (itPlatos->second == 1) itMesas->second.erase(itPlatos);
        else itPlatos->second--;
        // Constante
        cocina.erase(itAux);
    }
    // Coste lineal en el caso peor, logaritmico en el caso general
    pair<int, string> servir() {
        // Constante
        if (cocina.empty()) throw domain_error("No hay pedidos pendientes");
        // Constante
        pair<int, string>p = cocina.front();
        // Constante
        cocina.pop_front();
        // Constante de media, lineal en el peor caso
        unordered_map<int, map<string, int>>::iterator itMesas = mesas.find(p.first);
        // Logaritmico al ser un mapa ordenado
        map<string, int>::iterator itPlato = itMesas->second.find(p.second);
        // Constante amortizado
        if (itPlato->second == 1) itMesas->second.erase(itPlato);
        else itPlato->second--;
        return p;
    }
    // Coste lineal
    vector<string> que_falta(int mesa) const {
        // Constante de media, lineal en mesas.size() en el caso peor
        unordered_map<int, map<string, int>>::const_iterator itMesas = mesas.find(mesa);
        if (itMesas == mesas.cend()) throw domain_error("Mesa vacia");
        vector<string>ret{};
        // Lineal en el itMesas->second.size() (cantidad de platos distintos que ha pedido la mesa)
        for (map<string, int>::const_iterator it = itMesas->second.cbegin(); it != itMesas->second.cend(); it++) {
            ret.push_back(it->first);
        }
        return ret;
    }
};

bool resuelveCaso() {
    std::string orden, plato;
    int num;
    std::cin >> orden;
    if (!std::cin)
        return false;

    restaurante pedidos;

    while (orden != "FIN") {
        try {
            if (orden == "nueva_mesa") {
                cin >> num;
                pedidos.nueva_mesa(num);
            }
            else if (orden == "nuevo_pedido") {
                cin >> num >> plato;
                pedidos.nuevo_pedido(num, plato);
            }
            else if (orden == "cancelar_pedido") {
                cin >> num >> plato;
                pedidos.cancelar_pedido(num, plato);
            }
            else if (orden == "servir") {
                pair<int, string> p = pedidos.servir();
                cout << p.second << " " << p.first << "\n";
            }
            else if (orden == "que_falta") {
                cin >> num;
                vector<string> v = pedidos.que_falta(num);
                cout << "En la mesa " << 7 << " falta:\n";
                for (string s : v) cout << "  " << s << "\n";
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
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
