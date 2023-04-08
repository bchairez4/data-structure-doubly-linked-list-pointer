#ifndef NODE_H
#define NODE_H

//Handles all the pointers while List class handles new and delete
template <class T>
class Node {
    private:
        T data_;
        Node<T>* next_;
        Node<T>* prev_;
    public:
        Node();
        Node(const T& data, Node<T>* next, Node<T>* prev);
        Node(const Node<T>*& other);
        T& operator=(const Node<T>*& other);
        ~Node();
        T getData() const;
        Node<T>* getNext() const;
        Node<T>* getPrev() const;
        void setData(const T& data);
        void setNext(Node<T>*& node);
        void setPrev(Node<T>*& node);
};

#endif