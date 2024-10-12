//-------------------------------------------------------
// Ejercicio 1: Rotar una lista a la derecha. Mayo 2023
// Escribe tu nombre y respuestas en las zonas indicadas
//-------------------------------------------------------
//@ <answer>
// Nombre :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
//Añade las librerías que necesites:
//@ <answer>


//@ </answer>

using namespace std;


// ----------------------------------------------------------------
// Definición de la clase Dequeue vista en clase: lista doble circular con nodo fantasma
// ¡¡No la modifiques!!

template<typename T>
class Dequeue {
private:
    class Nodo {
    public:
        Nodo() : sig(nullptr), ant(nullptr) {}
        Nodo(const T &elem) : elem(elem), sig(nullptr), ant(nullptr) {}
        Nodo(Nodo *ant, const T &elem, Nodo *sig) : elem(elem), sig(sig), ant(ant) {}

        T elem;
        Nodo *sig;
        Nodo *ant;
    };

public:
    Dequeue() {
        prim = new Nodo();
        prim->sig = prim;
        prim->ant = prim;
    }

    Dequeue(const Dequeue &other) : Dequeue() {
        copy_nodes_from(other);
    }

    ~Dequeue() {
        delete_nodes();
    }

    void rotar_derecha();

    void push_front(const T &elem) {
        Nodo *new_node = new Nodo(prim, elem, prim->sig);
        prim->sig->ant = new_node;
        prim->sig = new_node;
    }

    void push_back(const T &elem) {
        Nodo *new_node = new Nodo(prim->ant, elem, prim);
        prim->ant->sig = new_node;
        prim->ant = new_node;
    }

    void pop_front() {
        assert (prim->sig != prim);
        Nodo *target = prim->sig;
        prim->sig = target->sig;
        target->sig->ant = prim;
        delete target;
    }

    void pop_back() {
        assert (prim->sig != prim);
        Nodo *target = prim->ant;
        target->ant->sig = prim;
        prim->ant = target->ant;
        delete target;
    }

    bool empty() const {
        return prim->sig == prim;
    };

    const T &front() const {
        assert (prim->sig != prim);
        return prim->sig->elem;
    }

    const T &back() const {
        assert (prim->sig != prim);
        return prim->ant->elem;
    }

    Dequeue &operator=(const Dequeue &other) {
        if (this != &other) {
            delete_nodes();
            prim = new Nodo();
            prim->sig = prim->ant = prim;
            copy_nodes_from(other);
        }
        return *this;
    }

    void display(std::ostream &out) const {
        out << "[";
        if (prim->sig != prim) {
            out << prim->sig->elem;
            Nodo *current = prim->sig->sig;
            while (current != prim) {
                out << ", " << current->elem;
                current = current->sig;
            }
        }
        out << "]";

    }

    void display() const {
        display(std::cout);
    }

private:
    Nodo *prim;

    void delete_nodes() {
        Nodo *current = prim->sig;
        while (current != prim) {
            Nodo *target = current;
            current = current->sig;
            delete target;
        }

        delete prim;
    }

    void copy_nodes_from(const Dequeue &other) {
        Nodo *current_other = other.prim->sig;
        Nodo *last = prim;

        while (current_other != other.prim) {
            Nodo *new_node = new Nodo(last, current_other->elem, prim);
            last->sig = new_node;
            last = new_node;
            current_other = current_other->sig;
        }
        prim->ant = last;
    }

//@ <answer>
//
// Zona private de la clase Dequeue    
//Añade aquí las funciones auxliares privadas que necesites

void dettach(Nodo* n) {
    n->ant->sig = n->sig;
    n->sig->ant = n->ant;
}
void attach(Nodo* n, Nodo* next) {
    Nodo* prev = next->ant;
    n->ant = prev;
    n->sig = next;
    next->ant = n;
    prev->sig = n;
}

//@ </answer>
};
//-----------------------------------------------------------------


//@ <answer>
//
//Escribe aquí la implementación de la función principal y
//las funciones auxiliares que necesites
//No olvides comentar el coste.

// Solución profesor:
template<typename T>
void Dequeue<T>::rotar_derecha() {
    Nodo* i = prim->sig;
    // Lista no vacia
    if (i->sig != prim && i->sig != prim->ant) {
        while (i != prim->sig->sig) {
            Nodo* next = i->sig->sig;
            if (next == prim) next = prim->sig;
            dettach(i);
            attach(i, next);
            i = next;
        }
    }
}



//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>

template<typename T>
std::ostream &operator<<(std::ostream &out, const Dequeue<T> &l) {
    l.display(out);
    return out;
}

bool resuelveCaso() {
    //Lectura
    int N;
    string valor;
    cin >> N;
    if (!cin)
        return false;
    Dequeue<string> lista;
    for (int i = 0; i < N; i++) {
        cin >> valor;
        lista.push_back(valor);
    }
    //llamada
    lista.rotar_derecha();
    cout << lista << endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
  return 0;

}
