#ifndef EVENTTASK_H
#define EVENTTASK_H

#include "Task.h"

/* Inherit from Task class */
class EventTask : public Task{
  public:
    EventTask() {};
    /* Constructor with arguements */
    EventTask(const Date & date_data,
              const std::string & desc,
              const TaskMetaData & data):
        Task{date_data, desc, data} {};

    EventTask(const Task* task): Task{task} {};
    
    ~EventTask() {}; 

    //virtual functions specific to the class
    std::string getTaskType() { return "Event"; };
    char getTypeAbbreviation() { return 'E'; };

    virtual void outputDetailed(std::ostream& out){
        out << "\tLocation: " << data.getLocation()
            << "\n\tTime: " << data.getTime() << "\n";
    };

    virtual void output_To_File(std::ofstream& out){
    out << "|" << data.getLocation()
        << "|" << data.getTime() << "\n";
 
    };
};

#endif 
