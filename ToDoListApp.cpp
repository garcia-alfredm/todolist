#include <algorithm>
#include <iomanip>
#include <sstream>

#include "ToDoListApp.h"

using namespace std; 
void ToDoListApp::run() {

	//NOTE: we are using out/in streams from the class level, not cin/cout
	//      directly. 
	out << "Welcome to your To-Do List! You may begin to enter commands or HELP.\n";

	string command;
	do {
		out << "> ";
		getline(in, command);

		//Convert entire command to uppercase for easy compares
		transform(command.begin(), command.end(), command.begin(), ::toupper);

		if (command == "PRINT") {
			executeCommandPrint();
		} else if (command == "DETAILED") {
			executeCommandPrint(false, true);
		} else if (command == "COMPLETED") {
			executeCommandPrint(true);
		} else if (command == "ADD") {
			executeCommandAddTask();
		} else if (command == "REMOVE") {
			executeCommandRemoveTask();
		} else if (command == "COMPLETE") {
			executeCommandCompleteTask();
		} else if (command == "SAVE") {
			executeCommandSave();
		} else if (command == "LOAD") {
			executeCommandLoad();
		} else if (command == "EXIT") {
			out << "Thank you for using To-Do List!\n";
			break;
		} else if (command == "HELP"){
			executeCommandHelp();
		}else {
			out << "Unknown Command (" << command << "). Try Again.\n";
		}
		out << "\n";
	} while (true);
    return;
}

/* Command to print user tasks lists
 * @completed: boolean value on whether to print the oustanding_
 * or complete_ lists
 * @detailed: boolean value on whether to print all details of tasks
 * Precondition: outstanding_ or compelete_ should be populated
 */
void ToDoListApp::executeCommandPrint(bool completed, bool detailed)
{
	//outstanding_ tasklist
	if(!completed && outstanding_.TaskSize() == 0){
		out << "You have no outstanding tasks." << endl;
		return;
	}
	//complete tasklist
	else if(completed && finished_.TaskSize() == 0){
		out << "You have no completed tasks." << endl;
		return;
	}
	else{
	    int list_size{0};
	    if(!completed){
			//get outstanding task list size
			list_size = outstanding_.TaskSize();
		}
		else{	
			//get completed list task size
            list_size = finished_.TaskSize();
		}
		
		Task *temp;
		for(int index = 1; index <= list_size; ++index){
			//get the pointer for the task list
            if(completed){
                temp = finished_.getTask(index);
            }
            else{
                temp = outstanding_.getTask(index);
            }
			//print out deadline
			out << index << ". "<< temp->getDeadline() << "-";

			if(temp->getTypeAbbreviation() == GENERIC){
				out << temp->getDescription() << endl;
			}
			else{	
				//print out appropriate task type
				out << "[" << temp->getTaskType() << "] " << temp->getDescription() << endl;

				if(detailed){
                    temp->outputDetailed(out);
				}
			}
		}
	}
    return;
}

/* Adds task to outstanding_ task list
 * Postcondition: new task is added to outstanding in order
 * of it's due date
 */
void ToDoListApp::executeCommandAddTask(){
	char type;
	int month {0}, day {0}, year {0};

	out << "What type of task is this?[G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
	in >> type;
	/* Make upper-case */
    type = toupper(type);

	out << "What is the deadline for this task (MM/DD/YYYY format)?" << endl;
	/* Format date */
	in >> setw(2) >> month;
    in.ignore();
	in >> setw(2) >> day;
    in.ignore();
	in >> setw(4) >> year;
    in.ignore();
    /* create Date object */
    Date deadline{month, day, year};
    /* Hold user input */
	std::string desc;
	out << "How would you describe this event?\n";
	getline(in, desc);

    switch(type){
    case GENERIC:
        AddTask(type, deadline, desc);
        break;
    case SHOPPING:{
        vector<string> shopping_list;
		string shopping_item;

		out << "What items to do you need to buy?\n" 
			<< "[Type your item and press ENTER to add another item. Type DONE to complete the list]\n";
		getline(in, shopping_item);

		//populate vector until user inputs DONE
		while(shopping_item != "DONE"){
			shopping_list.push_back(shopping_item);
			getline(in, shopping_item);
		};

		//create and add task to outstandling list
		TaskMetaData metadata{shopping_list};
		AddTask(type, deadline, desc, metadata);
        break;
	}
    case EVENT:{
		string location, d_time;
		
		out << "Where is this event taking place?\n";
		getline(in, location);
		out << "What time is this event taking place?\n";
		getline(in, d_time);

		//create and add task to outstandling list
		TaskMetaData metadata{location, d_time};
		AddTask(type, deadline, desc, metadata);
        break;
	}
    case HOMEWORK:{
		string subject;
		out << "What class is this homework for?\n";
		getline(in, subject);

		//create and add task to outstandling list
		TaskMetaData metadata{subject};
		AddTask(type, deadline, desc, metadata);
        break;
	}
    default:
		out << "Sorry, type not recognized. Try again\n";
        break;
    }
	out << "Task added successfully.\n";
    return;
}

/* Removes an outstanding_ task by their number
 * Precondition: outstanding_ task list must be populated
 * Postcondition: outstanding_ list has a task removed
 */
void ToDoListApp::executeCommandRemoveTask(){
	int input{0};
	out << "Which task would you like to remove?\n";
	in >> input;

	/* if user input is greater than outstanding size print error */
	if(input > outstanding_.TaskSize() || input <= 0){
		out << "You have entered an invalid task number.\n";
	}else{
		outstanding_.removeTask(input);
		out << "Task removed successfully.\n";
	}
    return;
}

/* Removes task from outstanding_ to complete_
 * Incorrect task number prints error
 */
void ToDoListApp::executeCommandCompleteTask(){
	int input{0};
	out << "Which task would you like to complete?" << endl;
	in >> input;

	if(input > outstanding_.TaskSize() ){
		out << "You have entered an invalid task number. " << endl;
	}else{
        Task* new_task = outstanding_.getTask(input);
        finished_.insert(new_task);
        outstanding_.removeTask(input);
		out << "Task was marked completed." << endl;
        in.ignore();
	}
    return;
}

/* Save outstanding_ list to a file
 * Precondition: outstanding_ list must be populated
 * Postcondition: outstanding_ list is saved to 
 * existing or new text file
 */
void ToDoListApp::executeCommandSave(){
	//if outstanding size is zero 
	if(outstanding_.TaskSize() == 0){
		out << "You have no outstanding tasks.\n";
	}
	else{
		//create ofstream object
		std::string file_location;
		std::ofstream save_file;

		out << "Where would you like to save your outstanding task?\n";
		getline(in, file_location);
		save_file.open(file_location);

		Task *temp;
		for(int i = 1; i <= outstanding_.TaskSize(); ++i){	
			temp = outstanding_.getTask(i);
			/* Template for all tasks*/
			save_file << temp->getTypeAbbreviation() << "|" 
					  << temp->getDeadline() << "|" 
                      << temp->getDescription();
            temp->output_To_File(save_file);

		}
		save_file.close();
		out << "Tasks saved successfully!\n";
	}
    return;
}

/* Load exsisting task file 
 * Precondition: task file must exists, be in correct format
 * Postcondition: any exsisting outstanding_ list will be erased
 */
void ToDoListApp::executeCommandLoad(){
	string file_name;
	out << "What file would you like to load outstanding tasks from?\n";
	//obtain file name from user
	getline(in, file_name);

	//create ifstream object and open file
	ifstream load_file;
	load_file.open(file_name);

	if(load_file.is_open() ){
        string type, desc, month, day, year;
        outstanding_.clearList();

		while(!load_file.eof() ){
			getline(load_file, type, '|');
            getline(load_file, month, '/');
            getline(load_file, day, '/');
            getline(load_file, year, '|');

            /* Use stringstream to cast appropriate type*/
            int d_month, d_day, d_year;
            std::stringstream(month) >> d_month;
            std::stringstream(day) >> d_day;
            std::stringstream(year) >> d_year;

            Date due_date{d_month, d_day, d_year};

            switch(type.front() ){
			case GENERIC:{
		        getline(load_file, desc);
                AddTask(GENERIC, due_date, desc);
                break;
            }
			case EVENT:{
                string location, time;
                getline(load_file, desc, '|');
                getline(load_file, location, '|');
                getline(load_file, time);
                TaskMetaData metadata{location, time};
                AddTask(EVENT, due_date, desc, metadata);
                break;
            }
            case HOMEWORK:{
                string subject;
                getline(load_file, desc, '|');
                getline(load_file, subject, '|');
                TaskMetaData metadata{subject};
                AddTask(HOMEWORK, due_date, desc, metadata);
                break;
            }
            case SHOPPING:{
                vector<string> shopping_list;
                string temp, text;
                getline(load_file, desc, '|');
                getline(load_file, temp);
                std::istringstream line{temp};
                while(getline(line, text, '|') ){
                    shopping_list.push_back(text);
                }
                TaskMetaData metadata{shopping_list};
                AddTask(SHOPPING, due_date, desc, metadata);
                break;
            }
            default:
                break;
			}
		}
		load_file.close();
		out << "Tasks loaded successfully!\n";
	}
	else{
		out << "Sorry, file failed to load.\n";
	}
    return;
}

/* Prints details on possible commands
 */
void ToDoListApp::executeCommandHelp(){
	out << "PRINT\n\tDisplay outstanding tasks in order of deadline.\n" 
		<< "DETAILED\n\tDisplay specialized task information.\n"
		<< "COMPLETED\n\tDisplay all completed tasks.\n"
		<< "ADD\n\tCreate a new task!\n"
		<< "REMOVE\n\tRemove an outstanding task.\n"
		<< "COMPLETE\n\tMark an outstanding task as completed.\n"
		<< "SAVE\n\tSave outstanding tasks to a text file.\n" 
		<< "LOAD\n\tLoad task list from a text file.\n"
		<< "EXIT\n\tExit the program.";
    return;
}

/* Helper function to add task to outstanding_ list
 * @type: type of task being created
 * @duedate: Date object with task's due date
 * @desc: string with task's description
 * @metadata: TaskMetaData object with task's metadata
 * Precondition: information on task must be formatted correctly
 * Postconditon: new task added to outstanding in correct location
 */
void ToDoListApp::AddTask(char type, Date duedate, std::string desc, TaskMetaData metadata){
    Task* new_task;
    
    switch(type){
    case GENERIC:
        new_task = new Task(duedate, desc, metadata);
        break;
    case HOMEWORK:
        new_task = new HomeworkTask(duedate, desc, metadata);
        break;
    case SHOPPING:
        new_task = new ShoppingTask(duedate, desc, metadata);
        break;
    case EVENT:
        new_task = new EventTask(duedate, desc, metadata);
        break;
    default:
        break;
    }
    outstanding_.insert(new_task);
    return;
}
