/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Manual implementation of std::list using dynamic nodes working as *
*    a doubly linked list.                                                   *
*    Progess: Basic implentation and methods complete.                       *
*****************************************************************************/

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.cpp"

//Takes care of new and delete for the nodes
template <class T>
class DoublyLinkedList {
    private:
        int size_;
        Node<T>* head_;

        Node<T>* search_(T& data);
        void deleteRecursive_(Node<T>*& node);
    public:
        DoublyLinkedList();
        DoublyLinkedList(Node<T>*& head);
        DoublyLinkedList(DoublyLinkedList<T>& other);
        ~DoublyLinkedList();
        T& operator=(const DoublyLinkedList<T>& other);
        T front();
        T back();
        Node<T>* getHead();
        void push_back(T& data);
        void push_front(T& data);
        void pop_back();
        void pop_front();
        void clear();
        void remove(T& data);
        void replace(T& replace, T& data);
        void reverse();
        bool contains(T& data);
        bool empty() const;
        int count(T& data);
        int size() const;
        void print();
};

#endif