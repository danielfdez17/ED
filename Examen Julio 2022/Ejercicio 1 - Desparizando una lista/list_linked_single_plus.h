/**
 * Implementación del TAD Lista mediante listas enlazadas simples.
 * Clase original de Manuel Montenegro. Adaptada por Ignacio Fábregas
 *
 * Versión con clase genérica, nodo fantasma, cabeza y cola.
 */

#ifndef __LIST_LINKED_SINGLE_PLUS_H
#define __LIST_LINKED_SINGLE_PLUS_H

#include <cassert>
#include <iostream>

using namespace std;

template<typename T>
class ListLinkedSingle {
protected:

    /** Nodo como structura */
    struct Node {
        T value;
        Node* next;
    };

public:
    /** O(1) */
    ListLinkedSingle() {
        head = new Node;
        head->next = nullptr;
        tail = head;
    }

    /** O(n) */
    ~ListLinkedSingle() {
        delete_list(head);
    }

    /** O(n) */
    ListLinkedSingle(const ListLinkedSingle& other) : head(copy_nodes(other.head)) {
        tail = nth_node(other.size() - 1);
    }

    /** O(1)*/
    void push_front(const T& elem) {
        Node* new_node = new Node{ elem, head->next };
        head->next = new_node;
        if (tail == head) //si la lista era unitaria
            tail = new_node;
    }

    /** O(1)*/
    void push_back(const T& elem);

    /** O(1) */
    void pop_front() {
        assert(head->next != nullptr);
        Node* old_head = head->next;
        head->next = head->next->next;
        delete old_head;
        if (head->next == nullptr)
            tail = head;
    }

    /** O(n) */
    void pop_back();

    /** O(n) */
    int size() const;

    /** O(1)*/
    bool empty() const {
        return head->next == nullptr;
    };

    /** O(1)*/
    const T& front() const {
        assert(head->next != nullptr);
        return head->next->value;
    }

    /** versión no constante de front  O(1)*/
    T& front() {
        assert(head->next != nullptr);
        return head->next->value;
    }

    /** O(1)*/
    const T& back() const {
        assert(tail != nullptr);
        return tail->value;
    }

    /** versión no constante de back O(1)*/
    T& back() {
        assert(tail != nullptr);
        return tail->value;
    }

    /** O(n)*/
    const T& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    /** versión no constante de at O(1)*/
    T& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;

    }

    /** escritura en un canal de salida O(n)*/
    void display(std::ostream& out) const;

    /** O(n)*/
    void display() const {
        display(std::cout);
    }

    /////////////////////////////////////////////////////////////////
    // MODIFICACIONES
    // El coste del algoritmo es lineal en el numero de elementos de la lista this, ya que hay que recorrerlos todos para saber si son pares o no
     void desparizar(ListLinkedSingle<int>& aux) {
        if (head->next != nullptr) { // Si this no esta vacia
            Node* anti = head, * i = head->next, *sigi = i->next;
            while (i != nullptr) {
                if (i->value % 2 == 0) { // Si es par
                    // Desenlazar i the this
                    if (i == head->next) { // Primero
                        head->next = sigi;
                    }
                    else if (i == tail) { // Ultimo
                        tail = anti;
                        tail->next = nullptr;
                    }
                    else { // Caso general
                        anti->next = sigi;
                    }

                    // Enlazar i en aux
                    if (aux.head == aux.tail) { // Lista vacia
                        aux.head->next = i;
                    }
                    else { // Lista no vacia
                        aux.tail->next = i;
                    }
                    aux.tail = i;
                    aux.tail->next = nullptr;
                }
                else { // Si es impar
                    anti = i;
                }
                i = sigi;
                if (sigi != nullptr) sigi = sigi->next;
            }
        }
    }
    /////////////////////////////////////////////////////////////////

private:
    /** puntero a la cabeza de la estructura de nodos*/
    Node* head;
    /** puntero a la cola de la estructura de nodos*/
    Node* tail;

    void delete_list(Node* start_node);
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};


template <typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

template <typename T>
void ListLinkedSingle<T>::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

template <typename T>
void ListLinkedSingle<T>::push_back(const T& elem) {
    Node* new_node = new Node{ elem, nullptr };
    tail->next = new_node;
    tail = tail->next;
}

template <typename T>
void ListLinkedSingle<T>::pop_back() {
    assert(head->next != nullptr);
    Node* previous = head;
    Node* current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
    tail = previous;
}

template <typename T>
int ListLinkedSingle<T>::size() const {
    int num_nodes = 0;

    Node* current = head->next;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}

template <typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T>
void ListLinkedSingle<T>::display(std::ostream& out) const {
    if (head->next != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << " " << current->value;
            current = current->next;
        }
    }
}


#endif
