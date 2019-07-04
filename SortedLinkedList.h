#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include "Node.h"

#include <stdexcept>

template<typename T, typename Comparator>
class SortedLinkedList{
  public:
    /* Default constructor */
    SortedLinkedList(): d_size(0), d_head(nullptr) {};
    /* Destructor */
    ~SortedLinkedList() { clear(); };

    /* Return size of sorted linked list */
    inline const int& size() { return d_size; };
    
    /*Determine whether sorted linked list is empty */
    bool isEmpty(){
        if(size() ){
            return false;
        }else{
            return true;
        }
    };

    /* Insert new node to SortedLinkedList
     * @data_: object to insert
     * @returns boolean value to successful insertion
     * Precondition: data_ has been initialized with appropriate values
     * Postcondition: node has been inserted to SortedLinkedList
     */
    bool insert(const T& data_){
        Comparator comparator;
        
        /* if sortedlinkedlist is empty, insert to head node */
        if(isEmpty() ){
            d_head = new Node<T>(data_);    
            ++d_size;
            return true;
        }
        /* if sortedlinkedlist has more than one value */
        else{
            Node<T>* new_node = new Node<T>(data_);
            /* if head node is less than inserted node, insert before head */
            if(comparator(new_node->data_, d_head->data_) ){
                new_node->next_ = d_head;
                d_head = new_node;
                ++d_size; 
                return true;
            }
            else{
                Node<T>* temp = d_head;
                /* iterate throught linked list until hit last node */
                while(temp->next_ != nullptr){
                    /* if inserted node is less than temp->next_ insert before it */
                    if(comparator(new_node->data_, temp->next_->data_) ){
                        new_node->next_ = temp->next_;
                        temp->next_ = new_node;
                        ++d_size;
                        return true;
                    }
                    temp = temp->next_;
                }
                /* if inserted node is greater than all the nodes, insert at last */
                temp->next_ = new_node;
                ++d_size;
                return true;
            }
        }
    };
    
    /* Obtain node at associated position
     * @pos: int value determines position of node
     * @returns node correspoinding to position or error code
     * Postcondition: method retrieves associate node from list
     */
    const T retrieve(const int& pos){
        /* if sortedlinkedlist is empty or position is greater than size */
        if( isEmpty() || pos > size() ){
            throw std::range_error("Invalid position.\n");
        }
        /* else iterate through list until node is reached */
        else{
            Node<T>* temp = d_head;
            for(int index = 1; index < pos; ++index)
            {
                temp = temp->next_;
            }
            return temp->data_; 
        }
    };

    /* Remove node by position in list
     * @pos: int value determines position of node
     * @returns boolean value whether method was successful or not
     * Postconditin: method removes associated node from list
     */
    bool remove(const int& pos){
        if(isEmpty() || pos > size() ){
            return false;
        }
        else if(pos == 1){
            Node<T>* delete_me = d_head;
            d_head = d_head->next_;

            delete delete_me;
            --d_size;

            return true;
        }
        //else iterate until node before to delete
        else{
            Node<T>* temp = d_head;
            //iterate to node before note to delete
            for(int index = 1; index < pos - 1; ++index){
                temp = temp->next_;
            }

            //point to node to delete
            Node<T>* delete_me = temp->next_;

            //if delete_me is last node
            if(delete_me->next_ == nullptr){
                delete delete_me;
                temp->next_ = nullptr;
                --d_size;
                return true;
            }
            else{
                //have previous node's next_ point to node after delete_me
                temp->next_ = delete_me->next_;
                delete delete_me;
                --d_size;
                return true;
            }
        }
    };
    
    /* Method deletes contents of SortedLinkedList
     * Precondition: List must not be empty
     * Postcondition: SortedLinkedList will be empty
     */
    void clear(){
        if(isEmpty() ){
            return;
        }
        else{   
            //is only size one, delete head node 
            if(d_head->next_ == nullptr){
                delete d_head;
                d_head = nullptr;
                --d_size;
                return;
            }
            else{
                Node<T>* delete_me = d_head;
                while(d_head != nullptr){
                    d_head = d_head->next_;
                    delete delete_me;
                    delete_me = d_head;
                    --d_size;
                }
                return;
            }
        }
    };

  private:
    /* Private data members */
    int d_size;
    Node<T>* d_head;
};

#endif
