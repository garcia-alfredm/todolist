#ifndef TASKLIST_H 
#define TASKLIST_H

#include "SortedLinkedList.h"
#include "Task.h"
#include "EventTask.h"
#include "HomeworkTask.h"
#include "ShoppingTask.h"

class TaskList {
  public:
    /* Default Constructor*/  
    TaskList() {};
    ~TaskList() {};
    
    /* Insert node to task list
     * @new_task: Task pointer to be inserted
     * Precondition: polymorphism ensures Task* can point to children classes
     * Postcondition: task list is expanded
     */
    inline void insert(Task* new_task){ task_list.insert(new_task); };

    /* Returns size of task list
     * @returns int value of list size
     */
    inline int TaskSize(){ return task_list.size(); };

    /* Retrieves pointer to task
     * @pos: position of task node to retreive
     * @returns appropriate task pointer
     */ 
    inline Task* getTask(const int& pos) { return task_list.retrieve(pos); };

    /* Removes task located at position
     * @pos: position of task node to remove
     * @returns boolean value for successfull removal
     * Postcondition: task is removed
     */
    inline bool removeTask(const int& pos){ return task_list.remove(pos); };

    /* Empties contents of list
     * Postcondition: private member task_list is emptied
     */
    inline void clearList(){ task_list.clear(); };
    
    /*comparator struct handles comparing tasks */
    struct TaskPointerComparator{
        /* Overload operator() to use as functor
         * @lhs: left side task pointer
         * @rhs: right side task pointer
         * Precondition: @lhs and @rhs are valid object pointers
         * Postcondition: determine appropriate order between @lhs and @rhs
         */
        bool operator()(const Task* lhs, const Task* rhs){
            if(lhs->getDeadline() == rhs->getDeadline() ){
                std::string lhs_string = lhs->getDescription(), rhs_string = rhs->getDescription();
                if(lhs_string.compare(rhs_string) < 0){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return (lhs->getDeadline() < rhs->getDeadline() );
            }
        };
    };

  private:
    SortedLinkedList<Task*, TaskPointerComparator> task_list;
};
#endif
