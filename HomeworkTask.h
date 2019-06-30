#ifndef HOMEWORKTASK_H
#define HOMEWORKTASK_H

#include "Task.h"
/* Inherit from Task class */
class HomeworkTask : public Task
{
  public:
    HomeworkTask() {};
    /* Three arguement constructor */
    HomeworkTask(const Date & date_data,
                 const std::string & desc,
                 const TaskMetaData & data):
        Task{date_data, desc, data} {};

    /*Copy constructor */
    HomeworkTask(const Task* task): Task{task} {}; 
    ~HomeworkTask() {};

    std::string getTaskType() { return "Homework"; };
    char getTypeAbbreviation() { return 'H'; };

    virtual void outputDetailed(std::ostream& out){
        out << "\tSubject: " << data.getSubject() << "\n";
    };

    virtual void output_To_File(std::ofstream& out){
        out << "|" << data.getSubject() << "\n";
    };
};

#endif
