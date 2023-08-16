#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <iostream>

#include "list.hpp"

template <typename T>
class List {
   private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    size_t size;

   public:
    List();
    void push(T data);
    T pop(int index);
    T at(int index);
    size_t length();
    void print();
};

template <typename T>
List<T>::List() : head(nullptr), size(0) {}

template <typename T>
void List<T>::push(T data) {
    Node* node = new Node{data, nullptr};
    if (head == nullptr) {
        head = node;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
    size++;
}

template <typename T>
T List<T>::pop(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    if (index == 0) {
        head = head->next;
        T data = current->data;
        delete current;
        size--;
        return data;
    }
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node* node_to_delete = current->next;
    T data = node_to_delete->data;
    current->next = node_to_delete->next;
    delete node_to_delete;
    size--;
    return data;
}

template <typename T>
T List<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
size_t List<T>::length() {
    return size;
}

template <typename T>
void List<T>::print() {
    std::cout << "[ ";
    for (size_t i = 0; i < size; i++) {
        std::cout << at(i);
        if (i != size - 1) std::cout << ", ";
    }
    std::cout << " ]";
}

#endif  // _LIST_HPP_
