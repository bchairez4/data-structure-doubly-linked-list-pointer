#ifndef NODE_H
#define NODE_H

#include <iostream>

//Handles all the pointers while List class handles new and delete
template <class T>
class Node {
    private:
        T data_;
        Node<T>* next_;
        Node<T>* prev_;
    public:
        Node();
        Node(T& data, Node<T>* next, Node<T>* prev);
        Node(const Node<T>*& other);
        T& operator=(const Node<T>*& other);
        ~Node();
        T getData();
        Node<T>* getNext();
        Node<T>* getPrev();
        void setData(T& data);
        void setNext(Node<T>*& node);
        void setPrev(Node<T>*& node);
        void getInfo();
};

#endif