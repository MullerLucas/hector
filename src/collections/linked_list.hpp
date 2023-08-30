#pragma once

#include <cstddef>
namespace hell {

// ----------------------------------------------

template <typename T>
struct LinkedListNode {
    T value;
    LinkedListNode<T>* next;
    LinkedListNode<T>* prev;
};

// ----------------------------------------------

template <typename T>
class LinkedList
{
private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;

public:
    LinkedList();

    void push_head(T value);
    void push_tail(T value);
    T pop_head();
    T pop_tail();
};

// ----------------------------------------------

template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr), tail(nullptr)
{ }

template <typename T>
void LinkedList<T>::push_head(T value) {
    auto new_node = new LinkedListNode<T>;
    new_node->value = value;
    new_node->next  = this->head;
    new_node->prev  = nullptr;

    if (this->head == nullptr) {
        this->tail = new_node;
    } else {
        this->head->prev = new_node;
    }

    this->head = new_node;
}

template <typename T>
void LinkedList<T>::push_tail(T value) {
    auto new_node = new LinkedListNode<T>;
    new_node->value = value;
    new_node->next  = nullptr;
    new_node->prev  = this->tail;

    if (this->tail == nullptr) {
        this->head = new_node;
    } else {
        this->tail->next = new_node;
    }

    this->tail = new_node;
}

// ----------------------------------------------

}
