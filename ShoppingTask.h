#ifndef SHOPPINGTASK_H
#define SHOPPINGTASK_H

#include "Task.h"

class ShoppingTask : public Task
{
  public:
    ShoppingTask() {};
    ShoppingTask(int month, int day, int year, std::string desc, const TaskMetaData& data);
    ShoppingTask(const Task* task);
    ~ShoppingTask() {};

    std::string getTaskType() { return "Shopping"; };
    char getTypeAbbreviation() { return 'S'; };
};

#endif  