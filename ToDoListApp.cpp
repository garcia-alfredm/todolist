#include <iostream> 
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "ToDoListApp.h"

using namespace std; 
void ToDoListApp::run() {

	//NOTE: we are using out/in streams from the class level, not cin/cout
	//      directly. All your functions should do this.
	out << "Welcome to your To-Do List! You may begin to enter commands.";
	out << endl;

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
		} else {
			out << "Unknown Command (" << command << "). Try Again.\n";
		}
		out << "\n";
	} while (true);
}

void ToDoListApp::executeCommandPrint(bool completed, bool detailed)
{
	//if completed is false
	if(!completed && my_tasks.TaskListSize(false) == 0)
	{
		out << "You have no outstanding tasks." << endl;
		return;
	}
	//if completed is true
	else if(completed && my_tasks.TaskListSize() == 0)
	{
		out << "You have no completed tasks." << endl;
		return;
	}
	else
	{
		int list_size = 0;
		if(!completed)
		{
			//get outstanding task list size
			list_size = my_tasks.TaskListSize(false);
		}
		else
		{	
			//get completed list task size
			list_size = my_tasks.TaskListSize();
		}
		
		Task *temp;
		for(int index = 1; index <= list_size; ++index)
		{
			//get the pointer for the outstanding or completed task list accordingly
			temp = my_tasks.retrieveTask(index, completed);
			Date deadline = temp->getDeadline();

			//print out deadline
			out << index << ". " 
				<< std::setfill('0') << std::setw(2) << deadline.getMonth() << "/" 
				<< std::setfill('0') << std::setw(2) << deadline.getDay() << "/" 
				<< std::setw(4) << deadline.getYear() << "-";

			if(temp->getTypeAbbreviation() == GENERIC)
			{
				//if pointer type is generic print out description
				out << temp->getDescription() << endl;
			}
			else
			{	
				//prit out appropriate task type
				out << "[" << temp->getTaskType() << "] " << temp->getDescription() << endl;

				if(detailed)
				{
					//get copy of task metadata
					TaskMetaData task_data = temp->getTaskMetadata();

					//print out appropriate meta data
					if(temp->getTypeAbbreviation() == HOMEWORK)
					{
						out <<"\tSubject:\n\t" << task_data.getSubject() << endl;
					}
					else if(temp->getTypeAbbreviation() == SHOPPING)
					{
						out << "\tItems:" << endl;

						vector<string> shopping = task_data.getShoppingList();
						for(unsigned int i = 0; i < shopping.size(); ++i)
						{
							out <<"\t" << shopping[i] << endl;
						}
					}
					else if(temp->getTypeAbbreviation() == EVENT) 
					{
						out << "\tLocation:\n\t" << task_data.getLocation()
							<< "\n\tTime:\n\t" << task_data.getTime() << endl;
					}
				}
			}
		}
	}
}

void ToDoListApp::executeCommandAddTask()
{
	char type;
	out << "What type of task is this?[G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
	in >> type;

	int month = 0, day = 0, year = 0;
	out << "What is the deadline for this task (MM/DD/YYYY format)?" << endl;
	//parse date input
	in >> setw(2) >> month;
	in.ignore();
	in >> setw(2) >> day;
	in.ignore();
	in >> setw(4) >> year;

	string desc;
	out << "How would you describe this task?" << endl;
	//flush i/o stream 
	in.ignore();
	getline(in, desc);

	if(type == GENERIC || type == 'g')
	{
		TaskMetaData metadata;

		//create and add task to outstandling list
		my_tasks.AddTask(type, month, day, year, desc, metadata);
	}

	else if(type == SHOPPING || type == 's')
	{
		vector<string> shopping_list;
		string shopping_item;

		out << "What items to do you need to buy?\n" 
			<< "[Type your item and press ENTER to add another item. Type DONE to complete the list]\n";
		in.ignore();
		getline(in, shopping_item);

		//populate vector until user inputs DONE
		while(shopping_item != "DONE")
		{
			shopping_list.push_back(shopping_item);
			out.flush();
			getline(in, shopping_item);
		};

		//create and add task to outstandling list
		TaskMetaData metadata(shopping_list);
		my_tasks.AddTask(type, month, day, year, desc, metadata);
	}

	else if(type == EVENT || type == 'e')
	{
		string location, d_time;
		
		out << "Where is this event taking place?\n";
		getline(in, location);
		out.flush();
		out << "When is this event taking place?\n";
		getline(in, d_time);

		//create and add task to outstandling list
		TaskMetaData metadata(location, d_time);
		my_tasks.AddTask(type, month, day, year, desc, metadata);
	}

	else if(type == HOMEWORK || type == 'h')
	{
		string subject;
		out << "What subject is this homework for?\n";
		getline(in, subject);
		out.flush();

		//create and add task to outstandling list
		TaskMetaData metadata(subject);
		my_tasks.AddTask(type, month, day, year, desc, metadata);
	}
	else
	{
		out << "Sorry, type not recognizes. Try again" << endl;
		return;
	}
	out << "Task added successfully.\n";
}

void ToDoListApp::executeCommandRemoveTask() 
{
	int input = 0;
	out << "Which task would you like to remove?" << endl;

	in >> input;

	//if user input is greater than outstanding size
	//print error
	if(input > my_tasks.TaskListSize(false) )
	{
		out << "You have entered an invalid task number." << endl;
		in.ignore();
	}
	else
	{
		my_tasks.RemoveTask(input);
		out << "Task removed successfully." << endl;
		in.ignore();
	}
}

void ToDoListApp::executeCommandCompleteTask()
{
	int input = 0;
	out << "Which task would you like to complete?" << endl;
	in >> input;

	if(input > my_tasks.TaskListSize(false) )
	{
		out << "You have entered an invalid task number. " << endl;
		in.ignore();
	}
	else
	{
		my_tasks.CompleteTask(input);
		out << "Task was marked complete successfully." << endl;
		in.ignore();
	}
}

void ToDoListApp::executeCommandSave()
{
	//if outstanding size is zero 
	if(my_tasks.TaskListSize(false) == 0 )
	{
		out << "You have no outstanding tasks." << endl;
	}
	else
	{
		//create ofstream object
		string file_location;
		ofstream save_file;

		out << "Where would you like to save your outstanding task?" << endl;
		getline(in, file_location);

		//open file
		save_file.open(file_location);

		Task *temp;
		for(int i = 1; i < my_tasks.TaskListSize(false); ++i )
		{	
			//format data appropriately
			temp = my_tasks.retrieveTask(i, false);
			Date deadline = temp->getDeadline();

			save_file << temp->getTypeAbbreviation() << "|" 
					  << std::setfill('0') << std::setw(2) << deadline.getMonth() << "/" 
					  << std::setfill('0') << std::setw(2) << deadline.getDay() << "/" 
					  << std::setw(4) << deadline.getYear() << "|"
					  << temp->getDescription();
			
			save_file.flush();
			if(temp->getTypeAbbreviation() == 'H')
			{
				//get homework metadata and input subject
				TaskMetaData task_data = temp->getTaskMetadata();
				save_file << "|" << task_data.getSubject() << endl;
			}
			else if(temp->getTypeAbbreviation() == 'E')
			{
				//get event metadata and put location and time
				TaskMetaData task_data = temp->getTaskMetadata();
				save_file << "|" << task_data.getLocation()
						  << "|" << task_data.getTime() << endl;
			}
			else if(temp->getTypeAbbreviation() == 'S')
			{
				//get shopping metadata and input vector list
				TaskMetaData task_data = temp->getTaskMetadata();
				vector<string> shopping = task_data.getShoppingList();

				for(unsigned int i = 0; i < shopping.size(); ++i)
				{
					save_file << "|" << shopping[i];
				}
				save_file << endl;
			}
			save_file << endl;
		}
		save_file.close();
		out.flush();
		out << "Tasks saved successfully!\n";
	}
}

void ToDoListApp::executeCommandLoad()
{
	string file_name;
	out << "What file would you like to load outstanding tasks from?\n";
	//obtain file name from user
	getline(in, file_name);

	//create ifstream object and open file
	ifstream load_file;
	load_file.open(file_name);

	if(load_file.is_open() )
	{
		string type, month, day, year, desc;

		while(!load_file.eof() )
		{
			//parse using getline and appropriate delimeter
			getline(load_file, type, '|');
			getline(load_file, month, '/');
			getline(load_file, day, '/');
			getline(load_file, year, '|');
			
			if(type == "G")
			{
				getline(load_file, desc);

				//create new task and insert to outstnding 
				TaskMetaData metadata;
				my_tasks.AddTask('G', stoi(month), stoi(day), stoi(year), desc, metadata);
				load_file.clear();
			}
			else if(type == "E")
			{
				string location, time;
				getline(load_file, desc, '|');
				getline(load_file, location, '|');
				getline(load_file, time);

				//create event task and insert
				TaskMetaData metadata(location, time);
				my_tasks.AddTask('E', stoi(month), stoi(day), stoi(year), desc, metadata);
				load_file.clear();
			}
			else if(type == "H")
			{
				string subject;
				getline(load_file, desc, '|');
				load_file.clear();
				getline(load_file, subject, '|');

				//create homework task
				TaskMetaData metadata(subject);
				my_tasks.AddTask('H', stoi(month), stoi(day), stoi(year), desc, metadata);
				load_file.clear();
			}
			else if(type == "S")
			{
				vector<string> shopping_list;
				getline(load_file, desc, '|');

				string temp, text;
				getline(load_file, temp);
				load_file.clear();

				std::istringstream line(temp);

				while(getline(line, text, '|') )
				{
					shopping_list.push_back(text);
					load_file.clear();
				}
				
				//create shopping task
				TaskMetaData metadata(shopping_list);
				my_tasks.AddTask('S', stoi(month), stoi(day), stoi(year), desc, metadata);
				load_file.clear();
			}
		}
		load_file.close();
		out << "Tasks loaded successfully!\n";
	}
	else
	{
		out << "Sorry, file failed to load.\n";
		return;
	}
}