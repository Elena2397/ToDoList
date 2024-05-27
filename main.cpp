#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <regex>
#include <fstream>

struct ToDoList
{
    int number{};
    std::string name{};
    std::string description{};
    std::string date{};
};

void readFile(std::vector<ToDoList> &arrayToDoList)
{
    int id{};
    std::string nameTask{};
    std::string descriptionTask{};
    std::string delimiter = "\t";

    std::string str;
    std::ifstream MyReadFile("ToDoList.txt");
    std::string dateTaskFile{};
    int i{1};

    while (getline(MyReadFile, str))
    {

        size_t pos = 0;
        if ((pos = str.find(delimiter)) != std::string::npos)
        {
            id = i;
            str.erase(0, pos + delimiter.length());
            i++;
        }
        if ((pos = str.find(delimiter)) != std::string::npos)
        {
            nameTask = str.substr(0, pos);
            str.erase(0, pos + delimiter.length());
        }
        if ((pos = str.find(delimiter)) != std::string::npos)
        {
            descriptionTask = str.substr(0, pos);
            str.erase(0, pos + delimiter.length());
        }
        if ((pos = str.find(delimiter)) != std::string::npos)
        {
            dateTaskFile = str.substr(0, pos);
            str.erase(0, pos + delimiter.length());
        }

        arrayToDoList.push_back({id, nameTask, descriptionTask, dateTaskFile});
    }

    MyReadFile.close();
};

void writeFile(std::vector<ToDoList> &arrayToDoList)
{
    std::string delimiter = "\t";
    std::ofstream data("ToDoList.txt");
    for (int i = 0; i < arrayToDoList.size(); i++)
    {
        data << arrayToDoList[i].number << delimiter << arrayToDoList[i].name << delimiter << arrayToDoList[i].description << delimiter << arrayToDoList[i].date << delimiter << '\n';
    }
    data.close();
};

std::string checkedDate()
{
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
            std::cout << "The date is entered incorrectly, try again (dd/mm/gggg)\n";
        }
    }
    return dateTask;
};

void addTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    if (arrayToDoList.size() == 0)
    {
        readFile(arrayToDoList);
    }

    std::cout << "Enter name task: ";
    std::string nameTask{};
    std::getline(std::cin >> std::ws, nameTask);
    nameTask = nameTask.substr(0, 25);

    std::cout << "Enter description task: ";
    std::string descriptionTask{};
    std::getline(std::cin >> std::ws, descriptionTask);
    descriptionTask = descriptionTask.substr(0, 255);

    std::string dateTask = checkedDate();

    int id = arrayToDoList.size();
    id++;

    arrayToDoList.push_back({id, nameTask, descriptionTask, dateTask});

    writeFile(arrayToDoList);
    
    std::cout << "The task has been completed successfully!\n\n";
};

void updateTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    std::ifstream ToDoList("ToDoList.txt");
    if (ToDoList.is_open() == true)
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
            if (id >= 0 && id <= arrayToDoList.size())
            {
                for (int i{0}; i < arrayToDoList.size(); ++i)
                {
                    if (id == arrayToDoList[i].number)
                    {
                        while (true)
                        {
                            std::cout << "Enter the name of the field to be changed (name, descriptiod, date). If you want to log out, enter exit: ";
                            std::string nameField{};
                            std::cin >> nameField;
                            if (nameField == "name")
                            {
                                std::cout << "Enter new name task: ";
                                std::string nameTask{};
                                std::getline(std::cin >> std::ws, nameTask);

                                arrayToDoList[i].name = nameTask;
                                writeFile(arrayToDoList);
                            }
                            else if (nameField == "descriptiod")
                            {
                                std::cout << "Enter new description task: ";
                                std::string descriptionTask{};
                                std::getline(std::cin >> std::ws, descriptionTask);

                                arrayToDoList[i].description = descriptionTask;
                                writeFile(arrayToDoList);
                            }
                            else if (nameField == "date")
                            {
                                std::string dateTask = checkedDate();
                                arrayToDoList[i].date = dateTask;
                                writeFile(arrayToDoList);
                            }
                            else if (nameField == "exit")
                            {
                                break;
                            }
                            else
                            {
                                std::cout << "You entered the wrong field name. You need to enter: name, descriptiod, date. If you want to log out, enter exit.\n";
                            }
                        }
                    }
                }
            }
            if (id == -1)
            {
                break;
            }
        }
        std::cout << "The task has been completed successfully!\n\n";
    }
    else
    {
        std::cout << "File is not present\n";
        std::cout << "You can create a new file using the command - add\n";
        arrayToDoList.clear();
    }
};

void deleteTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{
    std::ifstream ToDoList("ToDoList.txt");
    if (ToDoList.is_open() == true)
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

                    writeFile(arrayToDoList);

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
                        writeFile(arrayToDoList);
                    }
                }

                if (nameTask == "exit")
                {
                    break;
                }

                if (size == arrayToDoList.size())
                {
                    std::cout << "There is no such taxi name. Repeat the name or press enter: exit\n";
                }
                else
                {
                    break;
                }
            }
        }
        std::cout << "The task has been completed successfully!\n\n";
    }
    else
    {
        std::cout << "File is not present\n";
        std::cout << "You can create a new file using the command - add\n";
        arrayToDoList.clear();
    }
};

void selectTaskToDoList(std::vector<ToDoList> &arrayToDoList)
{

    std::ifstream ToDoList("ToDoList.txt");
    if (ToDoList.is_open() == true)
    {
        while (true)
        {
            std::cout << "Enter the date and the comparison operator.\n";

            std::cout << "Enter comparison operator ('=','<','>','<=','>=', '* - all tasks', exit): ";
            std::string comparisonOperator{};
            std::getline(std::cin >> std::ws, comparisonOperator);

            if (comparisonOperator == "*")
            {
                for (auto e : arrayToDoList)
                {
                    std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                }
            }
            else if (comparisonOperator == "exit")
            {
                break;
            }
            else
            {
                std::string dateTask = checkedDate();

                int day = std::stoi(dateTask.substr(0, 2));
                int month = std::stoi(dateTask.substr(3, 2));
                int year = std::stoi(dateTask.substr(6, 4));

                if (comparisonOperator == "=")
                {
                    int count{0};
                    for (auto e : arrayToDoList)
                    {
                        if (year == std::stoi(e.date.substr(6, 4)) && month == std::stoi(e.date.substr(3, 4)) && day == std::stoi(e.date.substr(0, 2)))
                        {
                            std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        }
                        else
                        {
                            count++;
                        }
                    }
                    if (count == arrayToDoList.size())
                    {
                        std::cout << "The task was not found.\n";
                    }
                }
                else if (comparisonOperator == "<")
                {
                    int count{0};
                    for (auto e : arrayToDoList)
                    {
                        if ((day + month * 31 + year * 365) > (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 4)) * 31 + std::stoi(e.date.substr(0, 2))))
                        {
                            std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        }
                        else
                        {
                            count++;
                        }
                    }
                    if (count == arrayToDoList.size())
                    {
                        std::cout << "The task was not found.\n";
                    }
                }
                else if (comparisonOperator == ">")
                {
                    int count{0};
                    for (auto e : arrayToDoList)
                    {
                        if ((day + month * 31 + year * 365) < (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 4)) * 31 + std::stoi(e.date.substr(0, 2))))
                        {
                            std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        }
                        else
                        {
                            count++;
                        }
                    }
                    if (count == arrayToDoList.size())
                    {
                        std::cout << "The task was not found.\n";
                    }
                }
                else if (comparisonOperator == "<=")
                {
                    int count{0};
                    for (auto e : arrayToDoList)
                    {
                        if ((day + month * 31 + year * 365) >= (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 4)) * 31 + std::stoi(e.date.substr(0, 2))))
                        {
                            std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        }
                        else
                        {
                            count++;
                        }
                    }
                    if (count == arrayToDoList.size())
                    {
                        std::cout << "The task was not found.\n";
                    }
                }
                else if (comparisonOperator == ">=")
                {
                    int count{0};
                    for (auto e : arrayToDoList)
                    {
                        if ((day + month * 31 + year * 365) <= (std::stoi(e.date.substr(6, 4)) * 365 + std::stoi(e.date.substr(3, 4)) * 31 + std::stoi(e.date.substr(0, 2))))
                        {
                            std::cout << e.number << ' ' << e.name << ' ' << e.description << ' ' << e.date << '\n';
                        }
                        else
                        {
                            count++;
                        }
                    }
                    if (count == arrayToDoList.size())
                    {
                        std::cout << "The task was not found.\n";
                    }
                }
                else
                {
                    std::cout << "You have entered an invalid comparison operator. Enter '=','<','>','<=','>=' or exit to exit the program.\n";
                }
            }
        }
        std::cout << "The task has been completed successfully!\n\n";
    }
    else
    {
        std::cout << "File is not present\n";
        std::cout << "You can create a new file using the command - add\n";
        arrayToDoList.clear();
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
            updateTaskToDoList(arrayToDoList);
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
