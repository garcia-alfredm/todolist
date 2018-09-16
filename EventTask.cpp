#include "EventTask.h"

EventTask::EventTask(int month, int day, int year, std::string desc, const TaskMetaData& data):
    Task(month, day, year, desc, data)
{}

//copy constructor
EventTask::EventTask(const Task* task):
    Task(task)
{}