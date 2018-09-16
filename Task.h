#ifndef TASK_H
#define TASK_H

#include "Date.h"
#include "TaskMetaData.h"

class Task 
{
  public:
    Task() {};
    
    Task(int month, int day, int year, std::string desc, const TaskMetaData& data = TaskMetaData() );

    //copy constructor
    Task(const Task* task);

    virtual ~Task() {};

    //instead of returning Date obj, should printout d_month, d_day, d_years
    const Date& getDeadline() const { return due_date; };

    //cannot return by reference b/c is temporary
    const std::string& getDescription() const { return description; };

    virtual std::string getTaskType() { return "Generic"; }; 

    virtual char getTypeAbbreviation() { return 'G'; };

    const TaskMetaData& getTaskMetadata() const {return data; }; 

  protected:
    Date due_date;
    std::string description;
    TaskMetaData data;
};

#endif