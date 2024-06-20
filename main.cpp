#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <QtCore/QCoreApplication>
#include <QSqlQuery>
#include "ToDoList.h"
#include "DBWork.h"

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
   DBWork dbWork;

   while (true)
   {
      std::string nameRecord{};
      std::cout << "Enter where the recording will be performed (to a file - file or to a database - db): ";
      std::cin >> nameRecord;

      if (nameRecord == "file")
      {
         while (true)
         {
            std::string nameTask{};
            std::cout << "Enter the name of the team: ";
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
         }
      }
      else if (nameRecord == "db")
      {
         while (true)
         {
            std::string nameTask{};
            std::cout << "Enter the name of the team: ";
            std::cin >> nameTask;

            if (nameTask == "add")
            {
               dbWork.addTaskFromDB();
            }
            else if (nameTask == "update")
            {
               dbWork.updateTaskFromDB();
            }
            else if (nameTask == "delete")
            {
               dbWork.deleteTaskFromDB();
            }
            else if (nameTask == "select")
            {
               dbWork.selectTaskFromDB();
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
         }
      }
      else if (nameRecord == "exit")
      {
         break;
      }
      else
      {
         std::cout << "Error: The write command was entered incorrectly. Enter 'file' if you want to write to a file. Enter 'db' if you want to write to the database. Enter 'exit' to exit the program.\n";
      }
   };

   return 0;
}
