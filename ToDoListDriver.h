#ifndef TODOLISTDRIVER_H
#define TODOLISTDRIVER_H

#include "TaskList.h"

class ToDoListDriver 
{
  public:
    ToDoListDriver() {};
    ~ToDoListDriver() {};

    void AddTask(char type, int month, int day, int year, std::string desc, TaskMetaData metadata);

    Task* CreateTask(Task* task);

    int TaskListSize(bool completed = true);

    Task* retrieveTask(int pos, bool completed = true);

    bool RemoveTask(int pos);

    bool CompleteTask(int pos);

  private:
    TaskList incomplete, complete;
};

#endif