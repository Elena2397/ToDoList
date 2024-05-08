#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <regex>

struct ToDoList
{
    int number{};
    std::string name{};
    std::string description{};
    std::string date{};
};

std::vector<ToDoList> addTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    // std::cout << "Enter numner task: ";
    // int numberTask{};
    // std::cin >> numberTask;

    std::cout << "Enter name task: ";
    std::string nameTask{};
    std::getline(std::cin >> std::ws, nameTask);
    nameTask = nameTask.substr(0, 25);

    std::cout << "Enter description task: ";
    std::string descriptionTask{};
    std::getline(std::cin >> std::ws, descriptionTask);
    descriptionTask = descriptionTask.substr(0, 255);

    std::string dateTask{};
    std::regex regular("([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/(2[0-9][0-9][0-9])");
    std::regex regularFeb("([0-2][0-9])/(02)/(2[0-9][0-9][0-9])");

    while (true)
    {
        std::cout << "Enter date task: ";
        std::cin >> dateTask;

        if (std::regex_match(dateTask, regular))
        {
            if (std::string{dateTask[3]} == "0" && std::string{dateTask[4]} == "2")
            {
                if (std::regex_match(dateTask, regularFeb))
                {
                    break;
                }
                else
                {
                    std::cout << "The date is entered incorrectly, else month = 02, then day <=29\n";
                }
            }
            break;
        }
        else
        {
            std::cout << "The date is entered incorrectly, try again (dd/mm/gggg)!\n";
        }
    }

    int id = arrayToDoList.size();
    id++;

    arrayToDoList.push_back({id, nameTask, descriptionTask, dateTask});

    return arrayToDoList;
};

void updateTaskToDoList()
{
    std::cout << "Update\n";
};

std::vector<ToDoList> deleteTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    std::string deleteName{};
    std::cout << "Enter name for delete(id or name): ";
    std::getline(std::cin >> std::ws, deleteName);

    if (deleteName == "id")
    {
        while (true)
        {
            std::cout << "Enter id delete task: ";
            int number{};
            std::cin >> number;

            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter an integer value: ";
                std::cin >> number;
            }

            if (number >= 0 && number <= arrayToDoList.size())
            {
                for (int i{0}; i < arrayToDoList.size(); ++i)
                {
                    if (arrayToDoList[i].number == number)
                    {
                        arrayToDoList.erase(arrayToDoList.begin() + i);
                    }
                }

                for (int i{0}; i < arrayToDoList.size(); ++i)
                {
                    if (arrayToDoList[i].number > number)
                    {
                        arrayToDoList[i].number = i + 1;
                    }
                }

                break;
            }
            else
            {
                std::cout << "The number is entered incorrectly, an integer value must be entered. TodoList has tasks from 1 to " << arrayToDoList.size() << '\n';
            }
        }
    }
    else if (deleteName == "name")
    {
        while (true)
        {
            std::string nameTask{};
            std::cout << "Enter name task: ";
            std::getline(std::cin >> std::ws, nameTask);
            int size = arrayToDoList.size();

            for (int i{0}; i < arrayToDoList.size(); ++i)
            {
                if (nameTask == arrayToDoList[i].name)
                {
                    arrayToDoList.erase(arrayToDoList.begin() + i);
                    for (int j{0}; j < arrayToDoList.size(); ++j)
                    {
                        if (arrayToDoList[j].number > i)
                        {
                            arrayToDoList[j].number = j + 1;
                        }
                    }
                break;
                }
            }

            if(nameTask == "exit")
            {
                break;
            }

            if (size == arrayToDoList.size())
            {
                std::cout << "There is no such taxi name. Repeat the name or press enter: exit\n";
            } else
            {
                break;
            }

        }
    }

    return arrayToDoList;
};

void selectTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    for (auto e : arrayToDoList)
    {
        std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
    }
};

void showToDoList()
{
    std::cout << "ToDoList\n\n";
    std::cout << "To get started with ToDoLost, select one of the following commands:\n";
    std::cout << "1) add - to add a task\n\n";
    std::cout << "2) update - to update an existing task\n\n";
    std::cout << "3) delete - to delete an existing task\n\n";
    std::cout << "4) select  '=','<','<=' '>', '>=' - to select tasks for a given time interval\n\n";
    std::cout << "5) exit - exiting the program\n\n";
}

int main()
{

    std::vector<ToDoList> arrayToDoList{};

    showToDoList();

    while (true)
    {
        std::string nameTask{};
        std::cout << "Enter the required task: ";
        std::cin >> nameTask;

        if (nameTask == "add")
        {
            addTaskToDoList(arrayToDoList);
        }
        else if (nameTask == "update")
        {
            updateTaskToDoList();
        }
        else if (nameTask == "delete")
        {
            deleteTaskToDoList(arrayToDoList);
        }
        else if (nameTask == "select")
        {
            selectTaskToDoList(arrayToDoList);
        }
        else if (nameTask == "exit")
        {
            break;
        }
        else
        {
            std::cout << "The wrong command was entered\n";
            showToDoList();
        }
    };

    return 0;
}