#ifndef EVENTTASK_H
#define EVENTTASK_H

#include "Task.h"

/* Inherit from Task class */
class EventTask : public Task{
  public:
    EventTask() {};
    /* Constructor with 3 arguements */
    EventTask(const Date & date_data,
              const std::string & desc,
              const TaskMetaData & data):
        Task{date_data, desc, data} {};

    /* copy constructor */
    EventTask(const Task* task): Task{task} {};
    
    ~EventTask() {}; 

    /* overloaded virtual functions */
    std::string getTaskType() { return "Event"; };
    char getTypeAbbreviation() { return 'E'; };

    /* Formats output for detailed information
     * @out: ostream object target of stream insertion
     * Precondition: @out initialized with std::cout
     */
    virtual void outputDetailed(std::ostream& out){
        out << "\tLocation: " << data.getLocation()
            << "\n\tTime: " << data.getTime() << "\n";
    };
    
    /* Formats ouput for saving user data
     * @out: ofstream object receiving stream insertion
     * Precondition: @out initizialed to user supplied
     * file destination
     */
    virtual void output_To_File(std::ofstream& out){
    out << "|" << data.getLocation()
        << "|" << data.getTime() << "\n";
    };
};

#endif 
