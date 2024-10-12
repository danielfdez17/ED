/**
 * Implementaci�n din�mica del TAD Arbol Binario con conteo manual de referencias
 * (c) Marco Antonio G�mez Mart�n, 2012
 * Modificado por Ignacio F�bregas, 2022
*/
#ifndef __ARBIN_H
#define __ARBIN_H

#include "Exceptions.h"
#include "List.h" // Tipo devuelto por los recorridos
#include "Queue.h" // Tipo auxiliar para implementar el recorrido por niveles
#include <iomanip>   // setw
#include <iostream>  // endl 

/**
 * Implementaci�n din�mica del TAD Arbin utilizando
 * nodos con un puntero al hijo izquierdo y otro al
 * hijo derecho. La implementaci�n permite compartici�n
 * de estructura, manteniendola bajo control mediante
 * conteo de referencias. La implementaci�n, sin embargo,
 * es bastante artesanal, pues para no complicar el c�digo
 * excesivamente no se ha hecho uso de punteros inteligentes
 * que incrementen y decrementen autom�ticamente esas
 * referencias.
 *
 * Las operaciones son:
 * - ArbolVacio: -> Arbin. Generadora implementada en el constructor sin par�metros.
 * - Cons: Arbin, Elem, Arbin -> Arbin. Generadora implementada en un constructor con tres par�metros.
 * - hijoIz, hijoDr: Arbin - -> Arbin. Observadoras que devuelven el hijo izquiero o derecho de un �rbol.
 * - esVacio: Arbin -> Bool. Observadora que devuelve si un �rbol binario es vac�o.
 */

template <typename T>
class Arbin {
protected:
	/**
	 * Clase nodo que almacena internamente el elemento (de tipo T),
	 * y los punteros al hijo izquierdo y al hijo derecho, as�
	 * como el n�mero de referencias que hay.
	 */
	class Nodo {
	public:
		Nodo() : iz(nullptr), dr(nullptr), numRefs(0) {}
		Nodo(Nodo* iz, const T& elem, Nodo* dr) :
			elem(elem), iz(iz), dr(dr), numRefs(0) {
			if (iz != nullptr)
				iz->addRef();
			if (dr != nullptr)
				dr->addRef();
		}

		void addRef() { assert(numRefs >= 0); numRefs++; }
		void remRef() { assert(numRefs > 0); numRefs--; }

		T elem;
		Nodo* iz;
		Nodo* dr;

		int numRefs;
	};

public:

	/** Constructor; operacion ArbolVacio */
	Arbin() : ra(nullptr) {
	}

	/** Constructor; operacion Cons */
	Arbin(const Arbin& iz, const T& elem, const Arbin& dr) :
		ra(new Nodo(iz.ra, elem, dr.ra)) {
		ra->addRef();
	}

	Arbin(const T& elem) :
		ra(new Nodo(nullptr, elem, nullptr)) {
		ra->addRef();
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~Arbin() {
		libera();
		ra = nullptr;
	}

	/**
	 * Devuelve el elemento almacenado en la raiz
	 * error raiz(ArbolVacio)
	 * @return Elemento en la ra�z.
	 */
	const T& raiz() const {
		if (esVacio())
			throw EArbolVacio();
		return ra->elem;
	}

	/**
	 * Devuelve el sub�rbol izquierdo compartiendo memoria
	 * Es una operaci�n parcial (falla con el �rbol vac�o).
	*/
	Arbin hijoIz() const {
		if (esVacio())
			throw EArbolVacio();
		return Arbin(ra->iz);
	}

	/**
	 * Devuelve el sub�rbol derecho compartiendo memoria
	 * Es una operaci�n parcial (falla con el �rbol vac�o).
	*/
	Arbin hijoDr() const {
		if (esVacio())
			throw EArbolVacio();
		return Arbin(ra->dr);
	}

	/** Operaci�n observadora; devuelve si el �rbol es vac�o. */
	bool esVacio() const {
		return ra == nullptr;
	}

	// //
	// RECORRIDOS SOBRE EL �RBOL
	// //

	/** Devolvemos un puntero a lista */
	List<T>* preorden() const {
		List<T>* ret = new List<T>();
		preordenAcu(ra, *ret);
		return ret;
	}

	List<T>* inorden() const {
		List<T>* ret = new List<T>();
		inordenAcu(ra, *ret);
		return ret;
	}

	List<T>* postorden() const {
		List<T>* ret = new List<T>();
		postordenAcu(ra, *ret);
		return ret;
	}

	List<T>* niveles() const {
		List<T>* ret = new List<T>();
		if (!esVacio()) {
			Queue<Nodo*> porProcesar;
			porProcesar.push_back(ra);

			while (!porProcesar.empty()) {
				Nodo* visita = porProcesar.front();
				porProcesar.pop_front();
				ret->push_back(visita->elem);
				if (visita->iz != NULL)
					porProcesar.push_back(visita->iz);
				if (visita->dr != NULL)
					porProcesar.push_back(visita->dr);
			}
		}
		return ret;
	}

	// //
	// OTRAS OPERACIONES OBSERVADORAS
	// //

	/** Devuelve el n�mero de nodos de un �rbol. */
	unsigned int numNodos() const {
		return numNodosAux(ra);
	}

	/** Devuelve la talla del �rbol. */
	unsigned int talla() const {
		return tallaAux(ra);
	}

	/** Devuelve el n�mero de hojas de un �rbol. */
	unsigned int numHojas() const {
		return numHojasAux(ra);
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Arbin(const Arbin<T>& other) : ra(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Arbin<T>& operator=(const Arbin<T>& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operadores de comparaci�n. */
	bool operator==(const Arbin<T>& rhs) const {
		return comparaAux(ra, rhs.ra);
	}

	bool operator!=(const Arbin<T>& rhs) const {
		return !(*this == rhs);
	}

	/** Escritura de un �rbol
	 *  Adaptado de "ADTs, DataStructures, and Problem Solving with C++",
	 *  Larry Nyhoff, Person, 2015
	 */
	friend std::ostream& operator<<(std::ostream& o, const Arbin<T>& t) {
		o << "==== Tree =====" << std::endl;
		graph_rec(o, 0, t.ra);
		o << "===============" << std::endl;
		return o;
	}

	/** Lectura de �rboles en preorden */
	static Arbin<T> leerArbol(const T& repVacio) {
		T elem;
		std::cin >> elem;
		if (elem == repVacio)
			return Arbin<T>();
		else {
			Arbin<T> hi = leerArbol(repVacio);
			Arbin<T> hd = leerArbol(repVacio);
			return Arbin<T>(hi, elem, hd);
		}
	}

	/** Lectura de �rboles en inorden */
	static Arbin<T> leerArbolInorden() {
		char c;
		std::cin >> c;
		if (c == '.')
			return Arbin<T>();
		else {
			assert(c == '(');
			Arbin<T> left = leerArbolInorden();
			T elem;
			std::cin >> elem;
			Arbin<T> right = leerArbolInorden();
			std::cin >> c;
			assert(c == ')');
			Arbin<T> result(left, elem, right);
			return result;
		}
	}



protected:
	/** para la escritura del �rbol */
	static const int TREE_INDENTATION = 4;

	/**
	 * Constructor protegido que crea un �rbol a partir de una estructura jer�rquica existente.
	 * Esa estructura jer�rquica SE COMPARTE, por lo que se a�ade la referencia.
	 * Se utiliza en hijoIz e hijoDr.
	 */
	Arbin(Nodo* raiz) : ra(raiz) {
		if (ra != nullptr)
			ra->addRef();
	}

	/** Operaci�n auxiliar para liberar la memoria */
	void libera() {
		libera(ra);
	}

	/** copia */
	void copia(const Arbin& other) {
		assert(this != &other);
		ra = other.ra;
		if (ra != nullptr)
			ra->addRef();
	}

	// //
	// M�TODOS AUXILIARES PARA LOS RECORRIDOS
	// //

	static void preordenAcu(Nodo* ra, List<T>& acu) {
		if (ra != nullptr) {
			acu.push_back(ra->elem);
			preordenAcu(ra->iz, acu);
			preordenAcu(ra->dr, acu);
		}
	}

	static void inordenAcu(Nodo* ra, List<T>& acu) {
		if (ra != nullptr) {
			inordenAcu(ra->iz, acu);
			acu.push_back(ra->elem);
			inordenAcu(ra->dr, acu);
		}
	}

	static void postordenAcu(Nodo* ra, List<T>& acu) {
		if (ra != nullptr) {
			postordenAcu(ra->iz, acu);
			postordenAcu(ra->dr, acu);
			acu.push_back(ra->elem);
		}
	}

	static void graph_rec(std::ostream& out, int indent, Nodo* raiz) {
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->dr);
			out << std::setw(indent) << " " << raiz->elem << std::endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->iz);
		}
	}

	// //
	// M�TODOS AUXILIARES (RECURSIVOS) DE OTRAS OPERACIONES
	// OBSERVADORAS
	// //

	static unsigned int numNodosAux(Nodo* ra) {
		if (ra == nullptr)
			return 0;
		return 1 + numNodosAux(ra->iz) + numNodosAux(ra->dr);
	}

	static unsigned int tallaAux(Nodo* ra) {
		if (ra == nullptr)
			return 0;
		int tallaiz = tallaAux(ra->iz);
		int talladr = tallaAux(ra->dr);
		if (tallaiz > talladr)
			return 1 + tallaiz;
		else
			return 1 + talladr;
	}

	static unsigned int numHojasAux(Nodo* ra) {
		if (ra == nullptr)
			return 0;

		if ((ra->iz == NULL) && (ra->dr == NULL))
			return 1;

		return numHojasAux(ra->iz) + numHojasAux(ra->dr);
	}

private:

	/**
	 * Elimina todos los nodos de una estructura arb�rea que comienza con el puntero ra.
	 * Se admite que el nodo sea nullptr
	 */
	static void libera(Nodo* ra) {
		if (ra != nullptr) {
			ra->remRef();
			if (ra->numRefs == 0) {
				libera(ra->iz);
				libera(ra->dr);
				delete ra;
			}
		}
	}

	/**
	 * Compara dos estructuras jer�rquicas de nodos, dadas sus raices.
	 */
	static bool comparaAux(Nodo* r1, Nodo* r2) {
		if (r1 == r2)
			return true;
		else if ((r1 == nullptr) || (r2 == nullptr))
			// En el if anterior nos aseguramos de que r1 != r2. Si uno es NULL, el
			// otro entonces no lo ser�, luego son distintos.
			return false;
		else {
			return (r1->elem == r2->elem) &&
				comparaAux(r1->iz, r2->iz) &&
				comparaAux(r1->dr, r2->dr);
		}
	}

protected:
	/**
	 * Puntero a la ra�z de la estructura jer�rquica de nodos.
	 */
	Nodo* ra;
};

#endif // __ARBIN_H
