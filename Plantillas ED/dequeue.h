/**
 * Implementación del TAD Doble Cola utilizando una lista
 * doblemente enlazada circular (con nodo fantasma).
 * Implementación de Manuel Montenegro
 * Adaptado por Ignacio Fábregas
 */
  
  
#ifndef __DEQUEUE_H
#define __DEQUEUE_H

#include <cassert>
#include <iostream>


template <typename T>
class Dequeue {
private:
    /**
       * Clase nodo que almacena internamente el elemento (de tipo T),
       * y dos punteros, uno al nodo anterior y otro al nodo siguiente.
       * Ambos punteros podrían ser nullptr si el nodo es el primero y/o último de la lista enlazada.
       */
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
  
  const T & front() const {
    assert (prim->sig != prim);
    return prim->sig->elem;
  }

  const T & back() const {
    assert (prim->sig != prim);
    return prim->ant->elem;
  }

  Dequeue & operator=(const Dequeue &other) {
    if (this != &other) {
      delete_nodes();
        prim = new Nodo();
        prim->sig = prim->ant = prim;
      copy_nodes_from(other);
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const {
      display(std::cout);
  }

private:
  Nodo *prim; //únicamente un puntero al principio

  void delete_nodes();
  void copy_nodes_from(const Dequeue &other);
};



template <typename T>
void Dequeue<T>::delete_nodes() {
  Nodo *current = prim->sig;
  while (current != prim) {
    Nodo *target = current;
    current = current->sig;
    delete target;
  }

  delete prim;
}

template <typename T>
void Dequeue<T>::copy_nodes_from(const Dequeue &other) {
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


template <typename T>
void Dequeue<T>::display(std::ostream &out) const {
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

template <typename T>
std::ostream & operator<<(std::ostream &out, const Dequeue<T> &l) {
    l.display(out);
    return out;
}

#endif