#ifndef TASKLIST_H 
#define TASKLIST_H

#include "SortedLinkedList.h"
#include "Task.h"
#include "EventTask.h"
#include "HomeworkTask.h"
#include "ShoppingTask.h"

class TaskList 
{
  public:

    TaskList() {};
    ~TaskList() {};
    
    void insert( Task* new_task){ task_list.insert(new_task); };
    /*void PushTask(const EventTask& new_task){ task_list.insert(new_task); };
    void PushTask(const HomeworkTask& new_task){ task_list.insert(new_task); };
    void PushTask(const ShoppingTask& new_task){ task_list.insert(new_task); };*/

    int TaskSize(){ return task_list.size(); };

    Task* getTask(const int& pos) { return task_list.retrieve(pos); };

    bool removeTask(const int& pos){ return task_list.remove(pos); };
    
    //comparator struct handles comparing tasks
    struct TaskPointerComparator
    {
        bool operator()(const Task* lhs, const Task* rhs)
        {
            if(lhs->getDeadline() == rhs->getDeadline() )
            {
                std::string lhs_string = lhs->getDescription(), rhs_string = rhs->getDescription();

                if(lhs_string.compare(rhs_string) < 0)
                {
                    return true;
                }
                else 
                    return false;
            }
            else
            {
                return (lhs->getDeadline() < rhs->getDeadline() );
            }
        };
    };

  private:
    SortedLinkedList<Task*, TaskPointerComparator> task_list;
};

#endif