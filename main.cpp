#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include "ToDoList.h"

void showToDoList()
{
    std::cout << "To get started with ToDoLost, select one of the following commands:\n";
    std::cout << "1) add - to add a task\n\n";
    std::cout << "2) update - to update an existing task\n\n";
    std::cout << "3) delete - to delete an existing task\n\n";
    std::cout << "4) select  '=','<','<=' '>', '>=' - to select tasks for a given time interval\n\n";
    std::cout << "5) exit - exiting the program\n\n";
}

int main()
{
    std::cout << "ToDoList\n\n";
    showToDoList();
    ToDoList toDoList;

    while (true)
    {
        std::string nameTask{};
        std::cout << "Enter the required task: ";
        std::cin >> nameTask;

        if (nameTask == "add")
        {
            toDoList.addTaskToDoList();
        }
        else if (nameTask == "update")
        {
            toDoList.updateTaskToDoList();
        }
        else if (nameTask == "delete")
        {
            toDoList.deleteTaskToDoList();
        }
        else if (nameTask == "select")
        {
            toDoList.selectTaskToDoList();
        }
        else if (nameTask == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Error: The wrong command was entered\n";
            showToDoList();
        }
    };

    return 0;
}
