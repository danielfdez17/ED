//-------------------------------------------------------
// Ejercicio 3: Detective de Moda. Mayo 2023
// Escribe tu nombre y respuestas en las zonas indicadas
//-------------------------------------------------------
//@ <answer>
// Nombre :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
//Añade las librerías que necesites:
//@ <answer>
#include<deque>
#include<unordered_map>
#include<unordered_set>
#include<set>

//@ </answer>

using namespace std;

using Color = string;

//@ <answer>
// Elige el tipo representante adecuado para el TAD TiendaCamisetas e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
// No olvides justificar la elección de los tipos y el coste de todas las operaciones.

class TiendaCamisetas {
    // SOLUCION 1
    // deque<Color> barra;
    // unordered_map<Color, int> camisetas;

    // SOLUCION 2
        deque<Color> barra;
        int posI, posD;
        unordered_map<Color, unordered_set<int>> camisetas;
        set<int>unicas;

public:
    // SOLUCION 1
    // Constante
    // TiendaCamisetas(){}
    // // Constante 
    // void inserta_izquierda(Color color) {
    //    barra.push_front(color);
    //    camisetas[color]++;
    // }
    // // Constante
    // void inserta_derecha(Color color) {
    //    barra.push_back(color);
    //    camisetas[color]++;
    // }
    // // Constante
    // void compra_izquierda() {
    //     if (barra.empty()) throw domain_error("Tienda sin camisetas");
    //     camisetas[barra.front()]--;
    //     barra.pop_front();
    // }
    // // Constante
    // void compra_derecha() {
    //     if (barra.empty()) throw domain_error("Tienda sin camisetas");
    //     camisetas[barra.back()]--;
    //     barra.pop_back();
    // }
    // // Cuadratico en en barra.size()
    // string pregunta() const {
    //    deque<Color>::const_iterator cabeza = barra.cbegin();
    //    deque<Color>::const_reverse_iterator cola = barra.crbegin();
    //    bool salirIz = false, salirdDr = false;
    //    int posI = 0, posD = (int)barra.size() - 1;
    //    while (cabeza != barra.cend() && !salirIz) {
    //         salirIz = camisetas.at(*cabeza) == 1;
    //         posI++; cabeza++;
    //    }
    //    while (cola != barra.crend() && !salirdDr) {
    //         salirdDr = camisetas.at(*cola) == 1;
    //         posD++; cola++;
    //    }
    //    string res = "";
    //    if (!salirIz && !salirdDr) res = "NADA INTERESANTE";
    //    else {
    //     if (posI < posD) res = to_string(posI) + " IZQUIERDA";
    //     else if (posD < posI) res = to_string(posD) + " IZQUIERDA";
    //     else res = to_string(posI) + "CUALQUIERA";
    //    }
    //    return res;
    // }

    // SOLUCION 2
    // Constante
    TiendaCamisetas(): posI(0), posD(0) {}
    // Logaritmico en unicas.size()
    void inserta_izquierda(Color color) {
        barra.push_front(color);
        unordered_map<Color, unordered_set<int>>::iterator itCamisetas = camisetas.find(color);
        if (itCamisetas == camisetas.end()) unicas.insert(posI);
        else {
            if (itCamisetas->second.size() == 1) unicas.erase(*itCamisetas->second.begin());
        }
        camisetas[color].insert(posI);
        posI--;
    }
    // Logaritmico en unicas.size()
    void inserta_derecha(Color color) {
        barra.push_front(color);
        unordered_map<Color, unordered_set<int>>::iterator itCamisetas = camisetas.find(color);
        if (itCamisetas == camisetas.end()) unicas.insert(posD);
        else {
            if (itCamisetas->second.size() == 1) unicas.erase(*itCamisetas->second.begin());
        }
        camisetas[color].insert(posD);
        posD++;
    }
    // Logaritmico en unicas.size()
    void compra_izquierda() {
        if (barra.empty()) throw domain_error("Tienda sin camisetas");
        Color comprado = barra.front();
        auto&s = camisetas[comprado];
        s.erase(posI + 1);
        if (s.empty()) {
            unicas.erase(posI + 1);
            camisetas.erase(comprado);
        }
        else if (s.size() == 1) unicas.insert(*s.begin());
        posI++;
        barra.pop_front();
    }
    // Logaritmico en unicas.size()
    void compra_derecha() {
        if (barra.empty()) throw domain_error("Tienda sin camisetas");
        Color comprado = barra.back();
        auto&s = camisetas[comprado];
        s.erase(posD);
        if (s.empty()) {
            unicas.erase(posD);
            camisetas.erase(comprado);
        }
        else if (s.size() == 1) unicas.insert(*s.begin());
        posD--;
        barra.pop_back();
    }
    // Constante
    string pregunta() const {
        string res = "";
        if (unicas.empty()) res = "NADA INTERESANTE";
        else {
            int compradasI = *unicas.cbegin() - posI;
            int compradasD = posD - *unicas.crbegin() + 1;
            if (compradasI == compradasD) res = to_string(compradasD) + " CUALQUIERA";
            else if (compradasI < compradasD) res = to_string(compradasI) + " IZQUIERDA";
            else res = to_string(compradasD) + " DERECHA";
        }
        return res;
    }
};


//@ </answer>
//
// ¡No modifiques nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelve() {
    string operacion;
    Color color;
    cin >> operacion;
    if (!cin)
        return false;

    TiendaCamisetas tienda;

    while (operacion != "FIN") {
        try {
            if (operacion == "inserta_izquierda") {
                cin >> color;
                tienda.inserta_izquierda(color);
            } else if (operacion == "inserta_derecha") {
                cin >> color;
                tienda.inserta_derecha(color);
            } else if (operacion == "compra_izquierda") {
                tienda.compra_izquierda();
            } else if (operacion == "compra_derecha") {
                tienda.compra_derecha();
            } else if (operacion == "pregunta") {
                cout << tienda.pregunta() << endl;
            }
        } catch (domain_error &e) {
            cout << "ERROR: " << e.what() << endl;
        }
        cin >> operacion;
    }
    cout << "---" << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("sample3.txt");
    // ofstream out("out.txt");
    // auto coutbuf = cout.rdbuf(out.rdbuf());
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve())
        ;
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;

}
