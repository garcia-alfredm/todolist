#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node 
{
    Node(const T& data = T() ): data(data), next(nullptr) {};
    Node(const T& data, Node<T>*& next): data(data), next(next) {};

    T data;
    Node<T>* next;
};

#endif