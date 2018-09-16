#include "ToDoListDriver.h"

//adds task pointer to the incompleted task list
void ToDoListDriver::AddTask(char type, int month, int day, int year, std::string desc, TaskMetaData metadata)
{
    Task* new_task;
    
    if(type == 'G')
    {
        new_task = new Task(month, day, year, desc, metadata);
    }
    else if(type == 'H')
    {
        new_task = new HomeworkTask(month, day, year, desc, metadata);
    }
    else if(type == 'S')
    {
       new_task = new ShoppingTask(month, day, year, desc, metadata);
    }
    else if(type == 'E')
    {
        new_task = new EventTask(month, day, year, desc, metadata);
    }

    incomplete.insert(new_task);
    return;
}

Task* ToDoListDriver::CreateTask(Task* task)
{
    if(task->getTypeAbbreviation() == 'G')
    { 
        return new Task(task); 
    }
    else if(task->getTypeAbbreviation() == 'E')
    {
        return new EventTask(task); 
    }
    else if(task->getTypeAbbreviation() == 'S')
    {
        return new ShoppingTask(task);
    }
    else if(task->getTypeAbbreviation() == 'H')
    {
        return new HomeworkTask(task);
    }
    else
    {
        return nullptr;
    }
}

int ToDoListDriver::TaskListSize(bool completed)
{   
    //completed is false, return incomplete task size
    if(!completed)
    {
        return incomplete.TaskSize();
    }
    //if completed is true, return complete list task size
    else
    {
        return complete.TaskSize();
    }
}

Task* ToDoListDriver::retrieveTask(int pos, bool completed)
{
    //completed is false, return incomplete task size
    if(!completed )
    {
        return incomplete.getTask(pos); 
    }
    //if completed is true, return complete list task size
    else
    {
        return complete.getTask(pos);
    }
}

bool ToDoListDriver::RemoveTask(int pos)
{
    return incomplete.removeTask(pos);
}

bool ToDoListDriver::CompleteTask(int pos)
{
    if(pos > TaskListSize(false) )
    {
        return false;
    }
    
    //create new pointer using copy constructor
    Task* new_task = CreateTask(retrieveTask(pos, false) );
    //push to complete list
    complete.insert(new_task);
    return RemoveTask(pos);       
}