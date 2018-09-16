#include "Task.h"

Task::Task(int month, int day, int year, std::string desc, const TaskMetaData& data):
    due_date(month, day, year), 
    description(desc),
    data(data)
{}

//copy constructor
Task::Task(const Task* task): 
    due_date(task->getDeadline() ), 
    description(task->getDescription() ), 
    data(task->getTaskMetadata() )
{}
