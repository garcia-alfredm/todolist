#ifndef EVENTTASK_H
#define EVENTTASK_H

#include "Task.h"

class EventTask : public Task
{
  public:
    EventTask() {};
    EventTask(int month, int day, int year, std::string desc, const TaskMetaData& data);
    EventTask(const Task* task);
    
    ~EventTask() {}; 

    //virtual functions specific to the class
    std::string getTaskType() { return "Event"; };
    char getTypeAbbreviation() { return 'E'; };
};

#endif 