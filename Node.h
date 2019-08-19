#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node 
{
    /* Default constructor */
    Node(const T& data = T() ): data_(data), next_(nullptr) {};
    /*Copy constructor*/
    Node(const T& data, Node<T>*& next): data_(data), next_(next) {};

    /* Node data member and next pointer */
    T data_;
    Node<T>* next_;
};

#endif
