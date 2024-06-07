#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include "Utils.h"

void readFile(std::vector<std::string> &arrayToDoListTasks)
{
    std::string str;
    std::ifstream MyReadFile("ToDoList.txt");

    while (getline(MyReadFile, str))
    {
        arrayToDoListTasks.push_back(str);
        str.clear();
    }

    MyReadFile.close();
};

void writeFile(std::vector<std::string> &arrayToDoListTasks)
{
    std::ofstream data("ToDoList.txt");
    
    for (int i = 0; i < arrayToDoListTasks.size(); i++)
    {
        data << arrayToDoListTasks[i] << '\n';
    }
    data.close();
};

std::string setCheckedDate()
{
    std::string dateTask{};
    std::regex regular("([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/(2[0-9][0-9][0-9])");
    std::regex regularFeb("([0-2][0-9])/(02)/(2[0-9][0-9][0-9])");

    while (true)
    {
        std::cout << "Enter date task (dd/mm/gggg): ";
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
                    std::cout << "Error: The date is entered incorrectly, else month = 02, then day <=29\n";
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            std::cout << "Error: The date was entered incorrectly, the year must be at least 2000 and no more than 2999, the correct date entry has the format (dd/mm/gggg). Please try again.. \n";
        }
    }
    return dateTask;
};