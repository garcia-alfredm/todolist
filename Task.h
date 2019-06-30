#ifndef TASK_H
#define TASK_H

#include <fstream>
#include <ostream>

#include "Date.h"
#include "TaskMetaData.h"

class Task 
{
  public:
    Task() {};
    /*3 parameter constructor */
    Task(const Date & date_data, 
         const std::string & desc, 
         const TaskMetaData & metadata = TaskMetaData() ):
        due_date{date_data}, 
        description{std::move(desc)},
        data{std::move(metadata)} {};

    /* copy constructor */
    Task(const Task* task):
        due_date{task->getDeadline() },
        description{task->getDescription() },
        data{task->getTaskMetadata() }
        {};

    virtual ~Task() {};

    const Date& getDeadline() const { return due_date; };

    const std::string& getDescription() const { return description; };

    virtual std::string getTaskType() { return "Generic"; }; 

    virtual char getTypeAbbreviation() { return 'G'; };

    const TaskMetaData& getTaskMetadata() const {return data; }; 

    virtual void outputDetailed(std::ostream& out){};

    virtual void output_To_File(std::ofstream& out){ out << "\n"; };

  protected:
    Date due_date;
    std::string description;
    TaskMetaData data;
};

#endif
