#ifndef SHOPPINGTASK_H
#define SHOPPINGTASK_H

#include "Task.h"
/* Inherit from Task class */
class ShoppingTask : public Task
{
  public:
    ShoppingTask() {};
    /* Three arguement constructor*/
    ShoppingTask(const Date& date_data,
                 const std::string & desc,
                 const TaskMetaData & data):
        Task{date_data, desc, data} {};

    /* Copy constructor*/
    ShoppingTask(const Task* task): Task{task} {};
    ~ShoppingTask() {};

    std::string getTaskType() { return "Shopping"; };
    char getTypeAbbreviation() { return 'S'; };

    virtual void outputDetailed(std::ostream& out){
        std::vector<std::string> list = data.getShoppingList();
        out << "\tItems:\n";
        for(unsigned int i{0}; i < list.size(); ++i){
            out << "\t  " << list[i] << "\n";
        }
    };

    virtual void output_To_File(std::ofstream& out){
        std::vector<std::string> shopping = data.getShoppingList();
        for(unsigned int i {0}; i < shopping.size(); ++i){
		    out << "|" << shopping[i];
		}
        out << "\n";
    };
};

#endif  
