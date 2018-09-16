#ifndef HOMEWORKTASK_H
#define HOMEWORKTASK_H

#include "Task.h"

class HomeworkTask : public Task
{
  public:
    HomeworkTask() {};
    HomeworkTask(int month, int day, int year, std::string desc, const TaskMetaData& data);
    HomeworkTask(const Task* task); 
    ~HomeworkTask() {};

    std::string getTaskType() { return "Homework"; };
    char getTypeAbbreviation() { return 'H'; };
};

#endif