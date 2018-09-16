#ifndef TASKMETADATA_H
#define TASKMETADATA_H

#include<string>
#include<vector>

class TaskMetaData 
{
  public:
    TaskMetaData() {};
    TaskMetaData(std::string location, std::string time); //constructor for event
    TaskMetaData(std::string subject); //constructor for homework
    TaskMetaData(std::vector<std::string> list); //constructor for shopping
    ~TaskMetaData() {};

    const std::string& getLocation() { return d_location; };
    const std::string& getTime() { return event_time; };
    const std::string& getSubject() { return d_subject; };
    const std::vector<std::string>& getShoppingList() { return shopping_list; };
    
  private:
    std::string d_location, event_time, d_subject;
    std::vector<std::string> shopping_list;
};

#endif