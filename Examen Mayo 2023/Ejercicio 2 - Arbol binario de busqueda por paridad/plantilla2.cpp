//---------------------------------------------------------------
// Ejercicio 2: Árbol binario de búsqueda por paridad. Mayo 2023
// Escribe tu nombre y respuestas en las zonas indicadas
//---------------------------------------------------------------
//@ <answer>
// Nombre :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <iostream>
#include <fstream>
#include <iomanip>   
#include <list>
#include <queue>
#include <iosfwd>
#include <cassert>
//Añade las librerías y constantes que necesites:
//@ <answer>

const int LIMITE = 10000;

//@ </answer>

using namespace std;

// ----------------------------------------------------------------
// Definición de la clase de Excepciones
// ¡No la modifiques!

class ExcepcionTAD {
public:
    ExcepcionTAD() {}
    ExcepcionTAD(const std::string &msg) : _msg(msg) {}

    const std::string msg() const { return _msg; }

    friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
    std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
    out << e._msg;
    return out;
}

#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

DECLARA_EXCEPCION(EArbolVacio);

// ----------------------------------------------------------------
// Definición de la clase Arbin
// ¡No la modifiques!

template <typename T>
class Arbin {
protected:
    class Nodo {
    public:
        Nodo() : iz(nullptr), dr(nullptr), numRefs(0) {}
        Nodo(Nodo *iz, const T &elem, Nodo *dr) :
                elem(elem), iz(iz), dr(dr), numRefs(0) {
            if (iz != nullptr)
                iz->addRef();
            if (dr != nullptr)
                dr->addRef();
        }

        void addRef() { assert(numRefs >= 0); numRefs++; }
        void remRef() { assert(numRefs > 0); numRefs--; }

        T elem;
        Nodo *iz;
        Nodo *dr;

        int numRefs;
    };

public:

    Arbin() : ra(nullptr) { }

    Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
            ra(new Nodo(iz.ra, elem, dr.ra)) {
        ra->addRef();
    }

    Arbin(const T &elem) :
            ra(new Nodo(nullptr, elem, nullptr)) {
        ra->addRef();
    }

    ~Arbin() {
        libera();
        ra = nullptr;
    }

    const T &raiz() const {
        if (esVacio())
            throw EArbolVacio();
        return ra->elem;
    }

    Arbin hijoIz() const {
        if (esVacio())
            throw EArbolVacio();
        return Arbin(ra->iz);
    }

    Arbin hijoDr() const {
        if (esVacio())
            throw EArbolVacio();
        return Arbin(ra->dr);
    }

    bool esVacio() const {
        return ra == nullptr;
    }

    // //
    // RECORRIDOS SOBRE EL ÁRBOL
    // //
    list<T>* preorden() const {
        list<T>* ret = new list<T>();
        preordenAcu(ra, *ret);
        return ret;
    }

    list<T>* inorden() const {
        list<T>* ret = new list<T>();
        inordenAcu(ra, *ret);
        return ret;
    }

    list<T>* postorden() const {
        list<T>* ret = new list<T>();
        postordenAcu(ra, *ret);
        return ret;
    }

    list<T>* niveles() const {
        list<T>* ret = new list<T>();
        if (!esVacio()){
            queue<Nodo*> porProcesar;
            porProcesar.push_back(ra);

            while (!porProcesar.empty()) {
                Nodo *visita = porProcesar.front();
                porProcesar.pop_front();
                ret->push_back(visita->elem);
                if (visita->iz != nullptr)
                    porProcesar.push_back(visita->iz);
                if (visita->dr != nullptr)
                    porProcesar.push_back(visita->dr);
            }
        }
        return ret;
    }

    // //
    // OTRAS OPERACIONES OBSERVADORAS
    // //

    unsigned int numNodos() const {
        return numNodosAux(ra);
    }

    unsigned int talla() const {
        return tallaAux(ra);
    }

    unsigned int numHojas() const {
        return numHojasAux(ra);
    }

    // //
    // MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
    // A LA CLASE
    // //

    Arbin(const Arbin<T> &other) : ra(NULL) {
        copia(other);
    }

    Arbin<T> &operator=(const Arbin<T> &other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }

    bool operator==(const Arbin<T> &rhs) const {
        return comparaAux(ra, rhs.ra);
    }

    bool operator!=(const Arbin<T> &rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& o, const Arbin<T>& t){
        o  << "==== Tree =====" << std::endl;
        graph_rec(o, 0, t.ra);
        o << "===============" << std::endl;
        return o;
    }

    static Arbin<T> leerArbolInorden() {
        char c;
        std::cin >> c;
        if (c == '.')
            return Arbin<T>(); 
        else {
            assert (c == '(');
            Arbin<T> left = leerArbolInorden();
            T elem;
            std::cin >> elem;
            Arbin<T> right = leerArbolInorden();
            std::cin >> c;
            assert (c == ')');
            Arbin<T> result(left, elem, right);
            return result;
        }
    }

protected:
    static const int TREE_INDENTATION = 4;

    Arbin(Nodo *raiz) : ra(raiz) {
        if (ra != nullptr)
            ra->addRef();
    }

    void libera() {
        libera(ra);
    }

    void copia(const Arbin &other) {
        assert(this != &other);
        ra = other.ra;
        if (ra != nullptr)
            ra->addRef();
    }

    // //
    // MÉTODOS AUXILIARES PARA LOS RECORRIDOS
    // //
    
    static void preordenAcu(Nodo *ra, list<T> &acu) {
        if (ra != nullptr){
            acu.push_back(ra->elem);
            preordenAcu(ra->iz, acu);
            preordenAcu(ra->dr, acu);
        }
    }

    static void inordenAcu(Nodo *ra, list<T> &acu) {
        if (ra != nullptr) {
            inordenAcu(ra->iz, acu);
            acu.push_back(ra->elem);
            inordenAcu(ra->dr, acu);
        }
    }

    static void postordenAcu(Nodo *ra, list<T> &acu) {
        if (ra != nullptr) {
            postordenAcu(ra->iz, acu);
            postordenAcu(ra->dr, acu);
            acu.push_back(ra->elem);
        }
    }

    static void graph_rec(std::ostream & out, int indent, Nodo* raiz){
        if (raiz != nullptr) {
            graph_rec(out, indent + TREE_INDENTATION, raiz->dr);
            out << std::setw(indent) << " " << raiz->elem << std::endl;
            graph_rec(out, indent + TREE_INDENTATION, raiz->iz);
        }
    }

    // //
    // MÉTODOS AUXILIARES (RECURSIVOS) DE OTRAS OPERACIONES
    // OBSERVADORAS
    // //

    static unsigned int numNodosAux(Nodo *ra) {
        if (ra == nullptr)
            return 0;
        return 1 + numNodosAux(ra->iz) + numNodosAux(ra->dr);
    }

    static unsigned int tallaAux(Nodo *ra) {
        if (ra == nullptr)
            return 0;
        int tallaiz = tallaAux(ra->iz);
        int talladr = tallaAux(ra->dr);
        if (tallaiz > talladr)
            return 1 + tallaiz;
        else
            return 1 + talladr;
    }

    static unsigned int numHojasAux(Nodo *ra) {
        if (ra == nullptr)
            return 0;

        if ((ra->iz == NULL) && (ra->dr == NULL))
            return 1;

        return numHojasAux(ra->iz) + numHojasAux(ra->dr);
    }

private:

    static void libera(Nodo *ra) {
        if (ra != nullptr) {
            ra->remRef();
            if (ra->numRefs == 0) {
                libera(ra->iz);
                libera(ra->dr);
                delete ra;
            }
        }
    }

    static bool comparaAux(Nodo *r1, Nodo *r2) {
        if (r1 == r2)
            return true;
        else if ((r1 == nullptr) || (r2 == nullptr))
            return false;
        else {
            return (r1->elem == r2->elem) &&
                   comparaAux(r1->iz, r2->iz) &&
                   comparaAux(r1->dr, r2->dr);
        }
    }

protected:

    Nodo *ra;
};
//-----------------------------------------------------------------
// 
//@<answer>
//
//Escribe tu solución. Usa las funciones y tipos de datos auxiales
// que consideres necesarios.


struct tsol {
    bool abbp;
    int minPar, maxPar, minImpar, maxImpar;
};



tsol abbp_aux(Arbin<int>const&arbol) {
    if (arbol.esVacio()) return {true, LIMITE, -LIMITE, -LIMITE, LIMITE}; 
    tsol i = abbp_aux(arbol.hijoIz());
    tsol d = abbp_aux(arbol.hijoDr());
    bool abbp; int minPar, maxPar, minImpar, maxImpar;
    if (arbol.raiz() % 2 == 0) {
        maxPar = max(arbol.raiz(), i.maxPar);
        minPar = min(arbol.raiz(), d.minPar);
        maxImpar = max(d.maxImpar, i.maxImpar);
        minImpar = min(d.minImpar, i.minImpar);
        abbp = i.abbp && d.abbp && arbol.raiz() < i.minPar && arbol.raiz() > d.maxPar;
    }
    else {
        maxImpar = max(arbol.raiz(), d.maxImpar);
        minImpar = min(arbol.raiz(), i.minImpar);
        maxPar = max(i.maxPar, d.maxPar);
        minPar = min(d.minPar, i.minPar);
        abbp = i.abbp && d.abbp && arbol.raiz() < d.minImpar && arbol.raiz() > i.maxImpar;
    }
    return {abbp, minPar, maxPar, minImpar, maxImpar};
}

string es_busqueda_par(Arbin<int>const&arbol) {
    return (abbp_aux(arbol).abbp ? "SI" : "NO");
}

//@ </answer>
//
// ¡No modifiques nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelve() {
    Arbin<int> arbol = Arbin<int>::leerArbolInorden();
    cout << es_busqueda_par(arbol) << endl;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelve();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;

}
