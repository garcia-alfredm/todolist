#include "HomeworkTask.h"

HomeworkTask::HomeworkTask(int month, int day, int year, std::string desc, const TaskMetaData& data):
    Task(month, day, year, desc, data)
{}

HomeworkTask::HomeworkTask(const Task* task):
    Task(task)
{}