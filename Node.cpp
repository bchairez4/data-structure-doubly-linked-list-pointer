#include "Node.h"

/*****************************************************************************
    Class Constructors/ Destructor
*****************************************************************************/
template<class T>
Node<T>::Node() : next_(nullptr), prev_(nullptr) {}

template <class T>
Node<T>::Node(T& data, Node<T>* next, Node<T>* prev): data_(data), next_(next), prev_(prev) {}

template <class T>
Node<T>::Node(const Node<T>*& other) {
    data_ = other->data_;
    next_ = other->next_;
    prev_ = other->prev_;
}

template <class T>
T& Node<T>::operator=(const Node<T>*& other) {
    data_ = other->data_;
    next_ = other->next_;
    prev_ = other->prev_;
}

template <class T>
Node<T>::~Node() {
    next_ = nullptr;
    prev_ = nullptr;
}

/*****************************************************************************
    Data Observation/Modification
*****************************************************************************/
template <class T>
T Node<T>::getData() {
    return data_;
}

template <class T>
Node<T>* Node<T>::getNext() {
    return next_;
}

template <class T>
Node<T>* Node<T>::getPrev() {
    return prev_;
}

template <class T>
void Node<T>::setData(T& data) {
    data_ = data;
}

template <class T>
void Node<T>::setNext(Node<T>*& node) {
    next_ = node;
}

template <class T>
void Node<T>::setPrev(Node<T>*& node) {
    prev_ = node;
}

template <class T>
void Node<T>::getInfo() {
    std::cout << "Node data: " << data_ << '\n';
    std::cout << "Node next: " << next_ << '\n';
    std::cout << "Node previous: " << prev_ << '\n';
    std::cout << '\n';
}