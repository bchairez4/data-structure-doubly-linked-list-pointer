#include "DoublyLinkedList.h"

/*****************************************************************************
    Constructors/ Destructor
*****************************************************************************/
// Time Complexity: O(1)
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : size_(0), head_(nullptr) {}

// Time Complexity: O(N), where N is the number of nodes from the head pointer.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(Node<T>*& head) : size_(0), head_(nullptr) {
    if (head == nullptr) {
        return;
    }
    
    Node<T>* curr_node = head;
    T data = curr_node->getData();

    Node<T>* new_node = new Node<T>(data, nullptr, nullptr);

    head_ = new_node;
    ++size_;

    Node<T>* temp_node = head_;
    curr_node = curr_node->getNext();
    while (curr_node != nullptr) {
        data = curr_node->getData();
        Node<T>* new_node = new Node<T>(data, nullptr, temp_node);
        
        temp_node->setNext(new_node);
        ++size_;

        curr_node = curr_node->getNext();
        temp_node = temp_node->getNext();
    }
}

// Time Complexity: O(N), where N is the number of elements in other.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>& other) : size_(0), head_(nullptr) {
    DoublyLinkedList<T> temp(other.head_);
    head_ = temp.getHead();
    size_ = temp.size();
}

// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

/*****************************************************************************
    Operator Overloading
*****************************************************************************/
// Time Complexity: O(N), where N is the number of elements in other.
template <class T>
T& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    DoublyLinkedList<T> temp(other.head_);
    head_ = temp.getHead();
    size_ = temp.size();
}

/*****************************************************************************
    Data Manipulation
*****************************************************************************/
//Returns data from the first node in the list !DO NOT USE WHEN LIST IS EMPTY!
// Time Complexity: O(1)
template <class T>
T DoublyLinkedList<T>::front() const {
    return head_->getData();
}

//Returns data from the last node in the list !DO NOT USE WHEN LIST IS EMPTY!
// Time Complexity: O(1)
template <class T>
T DoublyLinkedList<T>::back() const {
    Node<T>* curr_ptr = head_;
    while (curr_ptr->getNext() != nullptr) {
        curr_ptr = curr_ptr->getNext();
    }

    return curr_ptr->getData();
}

// Time Complexity: O(1)
template <class T>
Node<T>* DoublyLinkedList<T>::getHead() const {
    return head_;
}

//Pushes data to the back of the list
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::push_back(T& data) {
    //If empty, place at the start of the list
    if (empty()) {
        Node<T>* new_node = new Node<T>(data, nullptr, nullptr);

        head_ = new_node;
        ++size_;
        return;
    }

    // Travel to the last node of the list
    Node<T>* curr_node = head_;
    while (curr_node->getNext() != nullptr) {
        curr_node = curr_node->getNext();
    }

    // Place node directly after current last node in the list
    Node<T>* new_node = new Node<T>(data, nullptr, curr_node);

    curr_node->setNext(new_node);
    ++size_;
}

//Pushes data to the front of the list
// Time Complexity: O(1)
template <class T>
void DoublyLinkedList<T>::push_front(T& data) {
    // If empty directly place node in the front
    if (empty()) {
        Node<T>* new_node = new Node<T>(data, nullptr, nullptr);

        head_ = new_node;
        ++size_;
        return;
    }

    // Place new node in the front accounting for the previous front
    Node<T>* curr_node = head_;
    Node<T>* new_node = new Node<T>(data, curr_node, nullptr);

    curr_node->setPrev(new_node);
    head_ = new_node;
    ++size_;
}

//Removes last node from the list so long as it isnt empty
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        return;
    }

    // Travel to the last node in the list
    Node<T>* curr_node = head_;
    while(curr_node->getNext() != nullptr) {
        curr_node = curr_node->getNext();
    }

    // If the list has more than one item
    if (curr_node->getPrev() != nullptr) {
        Node<T>* null_node = nullptr;
        curr_node->getPrev()->setNext(null_node);
        delete curr_node;
        --size_;
        return;
    }

    // Else the list only has one item, account for head_ ptr
    head_ = nullptr;
    delete curr_node;
    --size_;
}

//Removes first node from the list so long as it isnt empty
// Time Complexity: O(1)
template <class T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        return;
    }

    Node<T>* curr_node = head_;
    
    // If the list has more than one item
    if (curr_node->getNext() != nullptr) {
        Node<T>* null_node = nullptr;
        head_ = curr_node->getNext();
        curr_node->getNext()->setPrev(null_node);
        delete curr_node;
        --size_;
        return;
    }

    // Else the list only has one item, account for head_ ptr
    head_ = nullptr;
    delete curr_node;
    --size_;
}

//Erases the entire list (Recursively)
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::clear() {
    deleteRecursive_(head_);
    head_ = nullptr;
}

//Searches list for data to remove
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::remove(const T& data) {
    //Make sure its in the list before proceeding, exiting if not found.
    if (!contains(data)) {
        return;
    }

    //search through list again knowing its in there
    Node<T>* curr_node = search_(data);

    //case 1: curr node is the only node in the list
    if (size() == 1) {
        head_ = nullptr;
        delete curr_node;
        --size_;
        return;
    }

    Node<T>* null_node = nullptr;
    //case 2: curr node is the first one in the list
    if(curr_node->getPrev() == nullptr && curr_node->getNext() != nullptr) {
        head_ = curr_node->getNext();
        curr_node->getNext()->setPrev(null_node);
        delete curr_node;
        --size_;
        return;
    }
    //case 3: curr node is the last one in the list
    else if (curr_node->getPrev() != nullptr && curr_node->getNext() == nullptr) {
        curr_node->getPrev()->setNext(null_node);
        delete curr_node;
        --size_;
        return;
    }
    //case 4: curr node is in the middle of the list
    else {
        Node<T>* left_node = curr_node->getPrev();
        Node<T>* right_node = curr_node->getNext();
        curr_node->getPrev()->setNext(right_node);
        curr_node->getNext()->setPrev(left_node);
        delete curr_node;
        --size_;
        return;
    }
}

//Searches for node containing replace to be overrided with data
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::replace(const T& replace, const T& data) {
    if (!contains(replace)) {
        return;
    }

    //Search through list knowing it's in there
    Node<T>* curr_node = search_(replace);

    curr_node->setData(data);
}

/*****************************************************************************
    Data observation
*****************************************************************************/
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
bool DoublyLinkedList<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }

    Node<T>* curr_node = head_;
    while (curr_node->getData() != data && curr_node->getNext() != nullptr) {
        curr_node = curr_node->getNext();
    }

    if (curr_node->getData() == data) {
        return true;
    }

    return false;
}

// Time Complexity: O(1)
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
int DoublyLinkedList<T>::count(const T& data) {
    if (empty()) {
        return 0;
    }

    int count = 0;

    Node<T>* curr_node = head_;
    while (curr_node != nullptr) {
        if (curr_node->getData() == data) {
            ++count;
        }
        curr_node = curr_node->getNext();
    }

    return count;
}

// Time Complexity: O(1)
template <class T>
int DoublyLinkedList<T>::size() const {
    return size_;
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
//Recursively deletes entire list node by node.
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
void DoublyLinkedList<T>::deleteRecursive_(Node<T>*& node) {
    if (node == nullptr) {
        return;
    }
    node = node->getNext();
    deleteRecursive_(node);

    delete node;
    --size_;
}

//Searching through the list knowing it exists. Recommended use after contains(data). RETURNS FIRST OCCURENCE
// Time Complexity: O(N), where N is the number of elements in the list.
template <class T>
Node<T>* DoublyLinkedList<T>::search_(const T& data) {
    Node<T>* curr_node = head_;
    while (curr_node->getData() != data) {
        curr_node = curr_node->getNext();
    }
    return curr_node;
}
