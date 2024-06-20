#ifndef TODOLIST_h
#define TODOLIST_h

#include <string>
#include <vector>

class ToDoList
{
private:
    struct Task
    {
        int number{};
        std::string name{};
        std::string description{};
        std::string date{};
    };

public:
    std::vector<ToDoList::Task> vectorTask{};
    void readTasksFormFile();
    void writeTasksFormFile();
    void addTaskToDoList();
    void updateTaskToDoList();
    void deleteTaskToDoList();
    void selectTaskToDoList();
};

#endif