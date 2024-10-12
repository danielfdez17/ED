/**
 * Implementaci�n del TAD lista, utilizando una lista doblemente enlazada.
 * (c) Marco Antonio G�mez Mart�n, 2012
 * Modificado por Ignacio F�bregas, 2022
*/
#ifndef __LIST_H
#define __LIST_H

#include "Exceptions.h"
#include <cassert>
using namespace std;

/**
 * Implementaci�n del TAD Lista utilizando una lista doblemente enlazada.
 * Las operaciones son:
 *    - EmptyList: -> List. Generadora implementada en el constructor sin par�metros.
 *    - push_front: List, Elem -> List. Generadora.
 *    - push_back: List, Elem -> List. Modificadora.
 *    - front: List - -> Elem. Observadora parcial
 *    - pop_front: List - -> List. Modificadora parcial
 *    - back: List - -> Elem. Observadora parcial
 *    - pop_back: List - -> List. Modificadora parcial
 *    - empty: List -> Bool. Observadora
 *    - size: List -> Entero. Obervadora.
 *    - at: List, Entero - -> Elem. Observador parcial.
 */
template <class T>
class List {
private:
	/**
	 * Clase nodo que almacena internamente el elemento (de tipo T),
	 * y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 * Ambos punteros podr�an ser nullptr si el nodo es el primero y/o �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : sig(nullptr), ant(nullptr) {}
		Nodo(const T& elem) : elem(elem), sig(nullptr), ant(nullptr) {}
		Nodo(Nodo* ant, const T& elem, Nodo* sig) : elem(elem), sig(sig), ant(ant) {}

		T elem;
		Nodo* sig;
		Nodo* ant;
	};

public:

	/** Constructor; operaci�n EmptyList. O(1) */
	List() : prim(nullptr), ult(nullptr), numElems(0) {}

	/** Destructor; elimina la lista doblemente enlazada. O(n) */
	~List() {
		libera();
	}

	/** A�ade un nuevo elemento en la cabeza de la lista. O(1) */
	void push_front(const T& elem) {
		prim = insertaElem(elem, nullptr, prim);
		if (ult == nullptr)
			ult = prim;
	}

	/** A�ade un nuevo elemento al final de la lista. O(1) */
	void push_back(const T& elem) {
		ult = insertaElem(elem, ult, nullptr);
		if (prim == nullptr) //si la lista estaba vac�a
			prim = ult;
	}

	/**
	 * Devuelve el valor almacenado en la cabecera de la lista.
	 * Es un error preguntar por el primero de una lista vac�a.
	 * O(1)
	 */
	const T& front() const {
		if (empty())
			throw EmptyListException("Cannot get front. The list is empty.");
		return prim->elem;
	}

	/**
	 * Devuelve el valor almacenado en la �ltima posici�n de la lista (a la derecha).
	 * Es un error preguntar por el primero de una lista vac�a.
	 * O(1)
	 */
	const T& back() const {
		if (empty())
			throw EmptyListException("Cannot get back. The list is empty.");
		return ult->elem;
	}

	/**
	 * Elimina el primer elemento de la lista. Es un error intentar obtener el resto de una lista vac�a.
	 * O(1)
	 */
	void pop_front() {
		if (empty())
			throw EmptyListException("Cannot pop. The list is empty.");
		Nodo* aBorrar = prim;
		prim = prim->sig;
		borraElem(aBorrar);
		if (prim == nullptr) //si la lista queda vac�a, modificamos tambi�n ult
			ult = nullptr;
	}

	/**
	 * Elimina el �ltimo elemento de la lista. Es un error intentar obtener el inicio de una lista vac�a.
	 * O(1)
	 */
	void pop_back() {
		if (empty())
			throw EmptyListException("Cannot pop. The list is empty.");
		Nodo* aBorrar = ult;
		ult = ult->ant;
		borraElem(aBorrar);
		if (ult == nullptr) //si la lista queda vac�a, modificamos tambi�n prim
			prim = nullptr;
	}

	/** Operaci�n observadora para saber si una lista tiene o no elementos. O(1) */
	bool empty() const {
		return prim == nullptr;
	}

	/** Devuelve el n�mero de elementos que hay en la lista. O(1) */
	unsigned int size() const {
		return numElems;
	}

	/**
	 * Devuelve el elemento i-�simo de la lista, teniendo en cuenta que el primer elemento (first())
	 * es el elemento 0 y el �ltimo es size()-1, es decir idx est� en [0..size()-1].
	 * Operaci�n observadora parcial que puede fallar si se da un �ndice incorrecto.
	 * O(n)
	*/
	const T& at(unsigned int idx) const {
		if (idx >= numElems)
			throw InvalidAccessException("Cannot get specified element. Invalid index");
		Nodo* aux = prim;
		for (int i = 0; i < idx; ++i)
			aux = aux->sig;
		return aux->elem;
	}

	// MODIFICACIONES
	// El coste del algoritmo es lineal en el numero de elementos de la lista
	void eliminar_elemento(const T& elem) {
		Nodo* i = prim;
		while (i != nullptr) {
			if (i->elem == elem) {
				Nodo* borrar = i;
				if (i == prim) {
					prim = i->sig;
					if (prim != nullptr) prim->ant = nullptr;
				}
				if (i == ult) {
					ult = i->ant;
					if (ult != nullptr) ult->sig = nullptr;
				}
				if (i->ant != nullptr && i->sig != nullptr) {
					i->ant->sig = i->sig;
					i->sig->ant = i->ant;
				}
				i = i->sig;
				numElems--;
				delete borrar;
			}
			else i = i->sig;
		}
	}

	// //
	// ITERADORES
	// //

	/**
	 * Clase interna que implementa un iterador sobre la lista que permite recorrer la lista pero no
	 * permite cambiarlos.
	 */
	class ConstIterator {
	public:
		ConstIterator() : act(nullptr) {}

		void next() {
			if (act == nullptr) throw InvalidAccessException();
			act = act->sig;
		}

		const T& elem() const {
			if (act == nullptr) throw InvalidAccessException();
			return act->elem;
		}

		bool operator==(const ConstIterator& other) const {
			return act == other.act;
		}

		bool operator!=(const ConstIterator& other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		ConstIterator& operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		/** Para que pueda construir objetos del tipo iterador */
		friend class List;

		ConstIterator(Nodo* act) : act(act) {}

		/** Puntero al nodo actual del recorrido */
		Nodo* act;
	};

	/**
	 * Clase interna que implementa un iterador sobre la lista que permite recorrer la lista e incluso
	 * alterar el valor de sus elementos.
	 */
	class Iterator {
	public:
		Iterator() : act(nullptr) {}

		void next() {
			if (act == nullptr) throw InvalidAccessException();
			act = act->sig;
		}

		const T& elem() const {
			if (act == nullptr) throw InvalidAccessException();
			return act->elem;
		}

		void set(const T& elem) const {
			if (act == nullptr) throw InvalidAccessException();
			act->elem = elem;
		}

		bool operator==(const Iterator& other) const {
			return act == other.act;
		}

		bool operator!=(const Iterator& other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		/** C�digo id�ntico al de elem() porque al ser const no se puede usar desde aqu�  */
		T& operator*() {
			if (act == nullptr) throw InvalidAccessException();
			return act->elem;
		}

		Iterator& operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		/** Para que pueda construir objetos del tipo iterador */
		friend class List;

		Iterator(Nodo* act) : act(act) {}

		/** Puntero al nodo actual del recorrido */
		Nodo* act;
	};

	// //
	// OPERADORES CON ITERADORES
	// //


	/** Devuelve el iterador constante al principio de la lista. O(1) */
	ConstIterator cbegin() const {
		return ConstIterator(prim);
	}

	/** Devuelve un iterador constante al final del recorrido (fuera de �ste). O(1) */
	ConstIterator cend() const {
		return ConstIterator(nullptr);
	}

	/** Devuelve el iterador no constante al principio de la lista. O(1) */
	Iterator begin() {
		return Iterator(prim);
	}

	/** Devuelve un iterador no constante al final del recorrido (fuera de �ste). O(1) */
	Iterator end() const {
		return Iterator(nullptr);
	}


	/**
	 * Permite eliminar de la lista el elemento apuntado por el iterador que se pasa como par�metro.
	 * El iterador recibido DEJA DE SER V�LIDO. En su lugar, deber� utilizarse el iterador devuelto, que
	 * apuntar� al siguiente elemento al borrado.
	 * @return Nuevo iterador colocado en el elemento siguiente al borrado.
	 * O(1).
	 */
	Iterator erase(const Iterator& it) {
		if (it.act == nullptr)
			throw InvalidAccessException("Cannot erase specified element. Iterator pointing to nullptr");
		// Cubrimos los casos especiales donde borramos alguno de los extremos
		if (it.act == prim) {
			pop_front();
			return Iterator(prim);
		}
		else if (it.act == ult) {
			pop_back();
			return Iterator(nullptr);
		}
		else {
			// El elemento a borrar es interno a la lista.
			Nodo* sig = it.act->sig;
			borraElem(it.act);
			return Iterator(sig);
		}
	}

	/**
	 * M�todo para insertar un elemento en la lista en el punto marcado por el iterador.
	 * En concreto, se a�ade _justo antes_ que el elemento actual. Por ejemplo, si it == l.primero(),
	 * el elemento insertado se convierte en el primer elemento (y el iterador apuntar� al segundo).
	 * O(1).
	 */
	void insert(const T& elem, const Iterator& it) {
		// Caso especial: a�adir al principio
		if (prim == it.act) {
			push_front(elem);
		}
		else
			// Caso especial: a�adir al final
			if (it.act == nullptr) {
				push_back(elem);
			}
		// Caso normal
			else {
				insertaElem(elem, it.act->ant, it.act);
			}
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL A LA CLASE
	// //

	/** Constructor copia. O(n) */
	List(const List<T>& other) : prim(nullptr), ult(nullptr) {
		copia(other);
	}

	/** Operador de asignaci�n. O(n) */
	List<T>& operator=(const List<T>& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. O(n) */
	bool operator==(const List<T>& rhs) const {
		if (numElems != rhs.numElems)
			return false;
		bool iguales = true;
		Nodo* p1 = prim;
		Nodo* p2 = rhs.prim;
		while ((p1 != nullptr) && (p2 != nullptr) && iguales) {
			if (p1->elem != p2->elem)
				iguales = false;
			else {
				p1 = p1->sig;
				p2 = p2->sig;
			}
		}
		return iguales;
	}

	bool operator!=(const List<T>& rhs) const {
		return !(*this == rhs);
	}


protected:

	void libera() {
		libera(prim);
		prim = nullptr;
		ult = nullptr;
	}

	/** Hacemos una copia con push_back */
	void copia(const List<T>& other) {
		prim = 0;
		numElems = 0;
		Nodo* act = other.prim;
		while (act != nullptr) {
			push_back(act->elem);
			act = act->sig;
		}
	}

private:

	/** Inserta un elemento entre el nodo1 y el nodo2. Devuelve el puntero al nodo creado. O(1)
	 * Caso general: los dos nodos existen.
	 *   nodo1->sig == nodo2
	 *   nodo2->ant == nodo1
	 * Casos especiales: alguno de los nodos no existe
	 *   nodo1 == nullptr y/o nodo2 == nullptr
	*/
	Nodo* insertaElem(const T& e, Nodo* nodo1, Nodo* nodo2) {
		Nodo* nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != nullptr)
			nodo1->sig = nuevo;
		if (nodo2 != nullptr)
			nodo2->ant = nuevo;
		numElems++;
		return nuevo;
	}

	/**
	 * Elimina el nodo n. Si el nodo tiene nodos antes o despu�s, actualiza sus punteros anterior y siguiente.
	 * No se puede borrar un nodo que sea nullptr.
	 * O(1)
	 */
	void borraElem(Nodo* n) {
		assert(n != nullptr);
		Nodo* pant = n->ant;
		Nodo* psig = n->sig;
		if (pant != nullptr)  //actualiza el puntero anterior si exist�a
			pant->sig = psig;
		if (psig != nullptr)  //actualiza el puntero siguiente si exist�a
			psig->ant = pant;
		numElems--;
		delete n;
	}

	/**
	 * Elimina todos los nodos de la lista enlazada cuyo primer nodo se pasa como par�metro.
	 * Se admite que el nodo sea nullptr (no habr� nada que liberar).
	 * En caso de pasarse un nodo v�lido, debe ser el primer nodo de la lista
	 */
	static void libera(Nodo* n) {
		//comprobamos que es el puntero al primer elemento
		assert(!n || !n->ant);
		while (n != nullptr) {
			Nodo* aux = n;
			n = n->sig;
			delete aux;
		}
	}

	// Puntero al primer y �ltimo elemento
	Nodo* prim, * ult;

	// N�mero de elementos (n�mero de nodos entre prim y ult)
	unsigned int numElems;
};

#endif // __LIST_H
