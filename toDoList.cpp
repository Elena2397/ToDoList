#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include <fstream>
#include <vector>
#include "Utils.h"
#include "ToDoList.h"

void ToDoList::readTasksFormFile()
{
    std::vector<std::string> vectorStr{};
    readFile(vectorStr);

    vectorTask.clear();
    int id{};
    int i{1};
    std::string nameTask{};
    std::string descriptionTask{};
    std::string delimiter = "\t";
    std::string dateTaskFile{};

    for (int i = 0; i < vectorStr.size(); i++)
    {
        size_t pos = 0;
        if ((pos = vectorStr[i].find(delimiter)) != std::string::npos)
        {
            id = i + 1;
            vectorStr[i].erase(0, pos + delimiter.length());
        }
        if ((pos = vectorStr[i].find(delimiter)) != std::string::npos)
        {
            nameTask = vectorStr[i].substr(0, pos);
            vectorStr[i].erase(0, pos + delimiter.length());
        }
        if ((pos = vectorStr[i].find(delimiter)) != std::string::npos)
        {
            descriptionTask = vectorStr[i].substr(0, pos);
            vectorStr[i].erase(0, pos + delimiter.length());
        }
        if ((pos = vectorStr[i].find(delimiter)) != std::string::npos)
        {
            dateTaskFile = vectorStr[i].substr(0, pos);
            vectorStr[i].erase(0, pos + delimiter.length());
        }
        vectorTask.push_back({id, nameTask, descriptionTask, dateTaskFile});
    }
};

void ToDoList::writeTasksFormFile()
{
    std::vector<std::string> vectorStr{};
    std::string delimiter = "\t";
    for (int i = 0; i < vectorTask.size(); i++)
    {
        std::string taskStr = std::to_string(vectorTask[i].number) + delimiter + vectorTask[i].name + delimiter + vectorTask[i].description + delimiter + vectorTask[i].date + delimiter;
        vectorStr.push_back(taskStr);
    }
    writeFile(vectorStr);
};

void ToDoList::addTaskToDoList()
{
    readTasksFormFile();

    std::cout << "Enter name task: ";
    std::string nameTask{};
    std::getline(std::cin >> std::ws, nameTask);
    nameTask = nameTask.substr(0, 25);

    std::cout << "Enter description task: ";
    std::string descriptionTask{};
    std::getline(std::cin >> std::ws, descriptionTask);
    descriptionTask = descriptionTask.substr(0, 255);

    std::string dateTask = setCheckedDate();

    int id = vectorTask.size();
    id++;

    vectorTask.push_back({id, nameTask, descriptionTask, dateTask});

    writeTasksFormFile();
    std::cout << "The task has been completed successfully!\n\n";
};

void ToDoList::updateTaskToDoList()
{
    readTasksFormFile();
    if (vectorTask.size() != 0)
    {
        while (true)
        {
            std::cout << "Enter the task id to update (if you want to log out, enter: -1): ";
            int id{};
            std::cin >> id;

            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter an integer value: ";
                std::cin >> id;
            }

            if (id >= 0 && id <= vectorTask.size())
            {
                for (int i{0}; i < vectorTask.size(); ++i)
                {
                    if (id == vectorTask[i].number)
                    {
                        while (true)
                        {
                            std::cout << "Enter the name of the field to be changed (name, description, date). If you want to log out, enter exit: ";
                            std::string nameField{};
                            std::cin >> nameField;

                            if (nameField == "name")
                            {
                                std::cout << "Enter new name task: ";
                                std::string nameTask{};
                                std::getline(std::cin >> std::ws, nameTask);
                                nameTask = nameTask.substr(0, 25);
                                vectorTask[i].name = nameTask;
                                writeTasksFormFile();
                                std::cout << "The task has been completed successfully!\n\n";
                            }
                            else if (nameField == "description")
                            {
                                std::cout << "Enter new description task: ";
                                std::string descriptionTask{};
                                std::getline(std::cin >> std::ws, descriptionTask);
                                descriptionTask = descriptionTask.substr(0, 255);
                                vectorTask[i].description = descriptionTask;
                                writeTasksFormFile();
                                std::cout << "The task has been completed successfully!\n\n";
                            }
                            else if (nameField == "date")
                            {
                                std::string dateTask = setCheckedDate();
                                vectorTask[i].date = dateTask;
                                writeTasksFormFile();
                                std::cout << "The task has been completed successfully!\n\n";
                            }
                            else if (nameField == "exit")
                            {
                                break;
                            }
                            else
                            {
                                std::cout << "Error: You entered the wrong field name. You need to enter: name, description, date. If you want to log out, enter exit.\n";
                            }
                        }
                    }
                }
            }
            if (id == -1)
            {
                break;
            }
            if (id > vectorTask.size())
            {
                std::cout << "There is no task with this id. There are tasks with id from 1 to " << vectorTask.size() << ". to exit, enter -1\n";
            }
        }
    }
    else
    {
        std::cout << "The task was not found\n";
        std::cout << "You can add a new task using the command - add\n";
    }
};

void ToDoList::deleteTaskToDoList()
{
    readTasksFormFile();
    if (vectorTask.size() != 0)
    {
        std::string deleteName{};
        std::cout << "Enter id or name delete the task: ";
        std::getline(std::cin >> std::ws, deleteName);
        deleteName = deleteName.substr(0, 25);

        if (deleteName == "id")
        {
            while (true)
            {
                std::cout << "Enter id delete task (-1 to exit the program): ";
                int number{};
                std::cin >> number;

                while (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter an integer value: ";
                    std::cin >> number;
                }

                if (number >= 0 && number <= vectorTask.size())
                {
                    for (int i{0}; i < vectorTask.size(); ++i)
                    {
                        if (vectorTask[i].number == number)
                        {
                            vectorTask.erase(vectorTask.begin() + i);
                        }
                    }

                    for (int i{0}; i < vectorTask.size(); ++i)
                    {
                        if (vectorTask[i].number > number)
                        {
                            vectorTask[i].number = i + 1;
                        }
                    }

                    writeTasksFormFile();
                    std::cout << "The task has been completed successfully!\n\n";
                    break;
                }
                else if (number == -1)
                {
                    break;
                }
                else
                {
                    std::cout << "Error: The number is entered incorrectly, an integer value must be entered. TodoList has tasks from 1 to " << vectorTask.size() << '\n';
                }
            }
        }
        else if (deleteName == "name")
        {
            while (true)
            {
                std::string nameTask{};
                std::cout << "Enter name task (exit - to exit the program): ";
                std::getline(std::cin >> std::ws, nameTask);
                int size = vectorTask.size();

                for (int i{0}; i < vectorTask.size(); ++i)
                {
                    if (nameTask == vectorTask[i].name)
                    {
                        vectorTask.erase(vectorTask.begin() + i);
                        for (int j{0}; j < vectorTask.size(); ++j)
                        {
                            if (vectorTask[j].number > i)
                            {
                                vectorTask[j].number = j + 1;
                            }
                        }
                        writeTasksFormFile();
                        std::cout << "The task has been completed successfully!\n\n";
                    }
                }

                if (nameTask == "exit")
                {
                    break;
                }

                if (size == vectorTask.size())
                {
                    std::cout << "Error: There is no such task name. Repeat the name or press enter: exit\n";
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        std::cout << "The task was not found\n";
        std::cout << "You can add a new task using the command - add\n";
    }
};

void ToDoList::selectTaskToDoList()
{
    readTasksFormFile();
    if (vectorTask.size() != 0)
    {
        while (true)
        {
            std::cout << "Enter comparison operator ('=','<','>','<=','>=', '* - all tasks', exit): ";
            std::string comparisonOperator{};
            std::getline(std::cin >> std::ws, comparisonOperator);

            if (comparisonOperator == "*")
            {
                for (auto e : vectorTask)
                {
                    std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                }
                std::cout << "The task has been completed successfully!\n\n";
            }
            else if (comparisonOperator == "exit")
            {
                break;
            }
            else if (comparisonOperator == "=" || comparisonOperator == "<" || comparisonOperator == ">" || comparisonOperator == "<=" || comparisonOperator == ">=")
            {

                std::string dateTask = setCheckedDate();

                int day = std::stoi(dateTask.substr(0, 2));
                int month = std::stoi(dateTask.substr(3, 2));
                int year = std::stoi(dateTask.substr(6, 4));
                bool flag = false;

                for (auto e : vectorTask)
                {
                    if (comparisonOperator == "=" && year == std::stoi(e.date.substr(6, 4)) && month == std::stoi(e.date.substr(3, 2)) && day == std::stoi(e.date.substr(0, 2)))
                    {
                        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        flag = true;
                    }
                    if (comparisonOperator == "<" && ((day + month * 31 + year * 365) > (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 2)) * 31 + std::stoi(e.date.substr(0, 2)))))
                    {
                        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        flag = true;
                    }
                    if (comparisonOperator == "<=" && ((day + month * 31 + year * 365) >= (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 2)) * 31 + std::stoi(e.date.substr(0, 2)))))
                    {
                        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        flag = true;
                    }
                    if (comparisonOperator == ">" && ((day + month * 31 + year * 365) < (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 2)) * 31 + std::stoi(e.date.substr(0, 2)))))
                    {
                        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        flag = true;
                    }
                    if (comparisonOperator == ">=" && ((day + month * 31 + year * 365) <= (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 2)) * 31 + std::stoi(e.date.substr(0, 2)))))
                    {
                        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        flag = true;
                    }
                }
                if (flag)
                {
                    std::cout << "The task has been completed successfully!\n\n";
                }
                else
                {
                    std::cout << "The task was not found.\n";
                }
            }
            else
            {
                std::cout << "Error: You have entered an invalid comparison operator. Enter '=','<','>','<=','>=' or exit to exit the program.\n";
            }
        }
    }
    else
    {
        std::cout << "The task was not found\n";
        std::cout << "You can add a new task using the command - add\n";
    }
};
