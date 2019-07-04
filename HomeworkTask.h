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

    /* overloaded virtual functions */
    std::string getTaskType() { return "Homework"; };
    char getTypeAbbreviation() { return 'H'; };

    /* Formats output for detailed information
     * @out: ostream object target of stream insertion
     * Precondition: @out initialized with std::cout
     */
    virtual void outputDetailed(std::ostream& out){
        out << "\tSubject: " << data.getSubject() << "\n";
    };

    /* Formats ouput for saving user data
     * @out: ofstream object receiving stream insertion
     * Precondition: @out initizialed to user supplied
     * file destination
     */
    virtual void output_To_File(std::ofstream& out){
        out << "|" << data.getSubject() << "\n";
    };
};

#endif
