#ifndef TASKMETADATA_H
#define TASKMETADATA_H

#include<string>
#include<vector>

class TaskMetaData 
{
  public:
    /* Generic Constructor */
    TaskMetaData() {};
    /* Event Constructor */
    TaskMetaData(std::string location, std::string time);
    /* Homework Constructor */
    TaskMetaData(std::string subject);
    /* Shopping task Constructor */
    TaskMetaData(std::vector<std::string> list);
    
    ~TaskMetaData() {};

    /* Getter methods */
    inline const std::string& getLocation() { return d_location; };
    inline const std::string& getTime() { return event_time; };
    inline const std::string& getSubject() { return d_subject; };
    inline const std::vector<std::string>& getShoppingList() { return shopping_list; };
    
  private:
    std::string d_location, event_time, d_subject;
    std::vector<std::string> shopping_list;
};

#endif
