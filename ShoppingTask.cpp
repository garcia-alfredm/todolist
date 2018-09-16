#include "ShoppingTask.h"

ShoppingTask::ShoppingTask(int month, int day, int year, std::string desc, const TaskMetaData& data):
    Task(month, day, year, desc, data)
{}

ShoppingTask::ShoppingTask(const Task* task):
    Task(task)
{}