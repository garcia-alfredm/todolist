#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include "Node.h"

#include <stdexcept>

template<typename T, typename Comparator>
class SortedLinkedList
{
  public:
    SortedLinkedList(): d_size(0), d_head(nullptr) {};
    ~SortedLinkedList() { clear(); };

    inline const int& size() { return d_size; };

    bool isEmpty()
    {
        if(size() )
        {
            return false;
        }
        else
        {
            return true;
        }
    };

    bool insert(const T& data)
    {
        Comparator comparator;
        
        //if sortedlinkedlist is empty, insert to head node
        if(isEmpty() )
        {
            d_head = new Node<T>(data);    
            ++d_size;
            return true;
        }
        //if sortedlinkedlist has more than one value
        else
        {
            Node<T>* new_node = new Node<T>(data);
            //if head node is less than inserted node, insert before head
            if(comparator(new_node->data, d_head->data) )
            {
                new_node->next = d_head;
                d_head = new_node;
                ++d_size; 
                return true;
            }
            else
            {
                Node<T>* temp = d_head;
                //iterate throught linked list until hit last node
                while(temp->next != nullptr)
                {
                    //if inserted node is less than temp->next insert before it
                    if(comparator(new_node->data, temp->next->data) )
                    {
                        new_node->next = temp->next;
                        temp->next = new_node;
                        ++d_size;
                        return true;
                    }
                    temp = temp->next;
                }
                //if inserted node is greater than all the nodes, insert at last
                temp->next = new_node;
                ++d_size;
                return true;
            }
        }
    };
    
    const T retrieve(const int& pos)
    {
        //if sortedlinkedlist is empty or position is greater than size
        if( isEmpty() || pos > size() )
        {
            throw std::range_error("Invalid position.\n");
        }
        //else iterate through list until node is reached 
        else
        {
            Node<T>* temp = d_head;
            for(int index = 1; index < pos; ++index)
            {
                temp = temp->next;
            }
            return temp->data; 
        }
    };
    
    bool remove(const int& pos)
    {
        if(isEmpty() || pos > size() )
        {
            return false;
        }
        
        //if list is size one delete and deincrement
        else if(pos == 1)
        {
            Node<T>* delete_me = d_head;
            d_head = d_head->next;

            delete delete_me;
            --d_size;

            return true;
        }
        //else iterate until node before to delete
        else
        {
            Node<T>* temp = d_head;
            //iterate to node before note to delete
            for(int index = 1; index < pos - 1; ++index)
            {
                temp = temp->next;
            }

            //point to node to delete
            Node<T>* delete_me = temp->next;

            //if delete_me is last node
            if(delete_me->next == nullptr)
            {
                delete delete_me;
                temp->next = nullptr;
                --d_size;
                return true;
            }
            else
            {
                //have previous node's next point to node after delete_me
                temp->next = delete_me->next;
                delete delete_me;
                --d_size;
                return true;
            }
        }
    };
    
    void clear()
    {
        //if linked list is empty, return
        if(isEmpty() )
        {
            return;
        }
        else
        {   
            //is only size one, delete head node 
            if(d_head->next == nullptr)
            {
                delete d_head;
                d_head = nullptr;
                --d_size;
                return;
            }
            else
            {
                Node<T>* delete_me = d_head;
                while(d_head != nullptr)
                {
                    d_head = d_head->next;
                    delete delete_me;
                    delete_me = d_head;
                    --d_size;
                }
                return;
            }
        }
    };

  private:
    int d_size;
    Node<T>* d_head;
};

#endif