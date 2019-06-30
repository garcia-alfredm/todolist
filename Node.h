#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node 
{
    Node(const T& data = T() ): data_(data), next_(nullptr) {};
    Node(const T& data, Node<T>*& next): data_(data), next_(next) {};
    //implement move constructor?

    T data_;
    Node<T>* next_;
};

#endif