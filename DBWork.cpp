#include <iostream>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlRecord>
#include "DBWork.h"
#include "ToDoList.h"
#include "Utils.h"

DBWork::DBWork() : db(new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL")))
{
    db->setHostName("localhost");
    db->setPort(5432);
    db->setUserName("postgres");
    db->setPassword("0000");
    db->setDatabaseName("ToDoList");
    db->open() ? std::cout << "Connection DB successfull!\n" : std::cout << "Error: Failed connection DB\n";
}

DBWork::~DBWork()
{
    db->close();
    delete db;
}

void DBWork::addTaskFromDB()
{
    std::cout << "Enter name task: ";
    std::string nameTask{};
    std::getline(std::cin >> std::ws, nameTask);
    nameTask = nameTask.substr(0, 25);

    std::cout << "Enter description task: ";
    std::string descriptionTask{};
    std::getline(std::cin >> std::ws, descriptionTask);
    descriptionTask = descriptionTask.substr(0, 255);

    std::string dateTask = setCheckedDate();

    QSqlQuery query;
    query.prepare("INSERT INTO public.tasks (nametask, descriptiontask, datetask) VALUES (:nameTask,:descriptionTask,:dateTask)");
    query.bindValue(":nameTask", QString::fromUtf8(nameTask.c_str()));
    query.bindValue(":descriptionTask", QString::fromUtf8(descriptionTask.c_str()));
    query.bindValue(":dateTask", QString::fromUtf8(dateTask.c_str()));
    if (!query.exec())
    {
        std::cout << "Eror: The entry has not been added. Error in the request.\n";
    }
    else
    {
        std::cout << "The record was deleted successfully.\n";
    }
}

void DBWork::deleteTaskFromDB()
{
    while (true)
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

                QSqlQuery select_q;
                select_q.prepare("SELECT FROM public.tasks WHERE id = :id");
                select_q.bindValue(":id", number);
                select_q.exec();
                if (select_q.next())
                {
                    QSqlQuery query;
                    query.prepare("DELETE FROM public.tasks WHERE id = :number;");
                    query.bindValue(":number", number);
                    query.exec();
                    std::cout << "The record was deleted successfully.\n";
                }
                else
                {
                    std::cout << "Error: There is no record with such an identifier in the database.\n";
                }

                if (number == -1)
                {
                    break;
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

                QSqlQuery select_q;
                select_q.prepare("SELECT FROM public.tasks WHERE nametask = :nametask");
                select_q.bindValue(":nametask", QString::fromUtf8(nameTask.c_str()));
                select_q.exec();

                if (select_q.next())
                {
                    QSqlQuery query;
                    query.prepare("DELETE FROM public.tasks WHERE nametask = :nametask");
                    query.bindValue(":nametask", QString::fromUtf8(nameTask.c_str()));
                    query.exec();
                    std::cout << "The record was deleted successfully.\n";
                }
                else
                {
                    std::cout << "Error: There is no record with such an identifier in the database.\n";
                }

                if (nameTask == "exit")
                {
                    break;
                }
            }
        }
        else if (deleteName != "name" || deleteName != "id" || deleteName != "exit")
        {
            std::cout << "Error: You entered the wrong command. Please enter the id to claim by id, name to search by name or exit to exit.\n";
        }
        if (deleteName == "exit")
        {
            break;
        }
    }
}

void DBWork::updateTaskFromDB()
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

        QSqlQuery select_q;
        select_q.prepare("SELECT FROM public.tasks WHERE id = :id");
        select_q.bindValue(":id", id);
        select_q.exec();
        if (select_q.next())
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
                    QSqlQuery name_q;
                    name_q.prepare("UPDATE public.tasks SET nametask = :nametask WHERE id = :id");
                    name_q.bindValue(":nametask", QString::fromUtf8(nameTask.c_str()));
                    name_q.bindValue(":id", id);
                    name_q.exec();
                    std::cout << "The task has been completed successfully!\n\n";
                }
                else if (nameField == "description")
                {
                    std::cout << "Enter new description task: ";
                    std::string descriptionTask{};
                    std::getline(std::cin >> std::ws, descriptionTask);
                    descriptionTask = descriptionTask.substr(0, 255);
                    QSqlQuery desc_q;
                    desc_q.prepare("UPDATE public.tasks SET descriptiontask = :descriptiontask WHERE id = :id");
                    desc_q.bindValue(":descriptiontask", QString::fromUtf8(descriptionTask.c_str()));
                    desc_q.bindValue(":id", id);
                    desc_q.exec();
                    std::cout << "The task has been completed successfully!\n\n";
                }
                else if (nameField == "date")
                {
                    std::string dateTask = setCheckedDate();
                    QSqlQuery date_q;
                    date_q.prepare("UPDATE public.tasks SET datetask = :datetask WHERE id = :id");
                    date_q.bindValue(":datetask", QString::fromUtf8(dateTask.c_str()));
                    date_q.bindValue(":id", id);
                    date_q.exec();
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
        else
        {
            std::cout << "Error: There is no record with such an identifier in the database.\n";
        }
        if (id == -1)
        {
            break;
        }
    }
}

void DBWork::selectTaskFromDB()
{
    while (true)
    {
        std::cout << "Enter comparison operator ('=','<','>','<=','>=', '* - all tasks', exit): ";
        std::string comparisonOperator{};
        std::getline(std::cin >> std::ws, comparisonOperator);

        if (comparisonOperator == "*")
        {
            QSqlQuery query;
            query.exec("SELECT * FROM tasks");
            while (query.next())
            {
                int id = query.value("id").toInt();
                QString nametask = query.value("nametask").toString();
                QString descriptiontask = query.value("descriptiontask").toString();
                QString datetask = query.value("datetask").toString();

                qDebug() << id << " " << nametask << "\t"
                         << descriptiontask << "\t" << datetask;
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

            QSqlQuery query;
            query.exec("SELECT * FROM tasks");
            while (query.next())
            {
                int id = query.value("id").toInt();
                QString nametask = query.value("nametask").toString();
                QString descriptiontask = query.value("descriptiontask").toString();
                QString datetask = query.value("datetask").toString();

                if (comparisonOperator == "=" && year == std::stoi(datetask.toStdString().substr(6, 4)) && month == std::stoi(datetask.toStdString().substr(3, 2)) && day == std::stoi(datetask.toStdString().substr(0, 2)))
                {
                    qDebug() << id << " " << nametask << "\t" << descriptiontask << "\t" << datetask;
                    flag = true;
                }

                if (comparisonOperator == "<" && ((day + month * 31 + year * 365) > (std::stoi(datetask.toStdString().substr(6, 4)) * 365 + std::stoi(datetask.toStdString().substr(3, 2)) * 31 + std::stoi(datetask.toStdString().substr(0, 2)))))
                {
                    qDebug() << id << " " << nametask << "\t" << descriptiontask << "\t" << datetask;
                    flag = true;
                }

                if (comparisonOperator == ">" && ((day + month * 31 + year * 365) < (std::stoi(datetask.toStdString().substr(6, 4)) * 365 + std::stoi(datetask.toStdString().substr(3, 2)) * 31 + std::stoi(datetask.toStdString().substr(0, 2)))))
                {
                    qDebug() << id << " " << nametask << "\t" << descriptiontask << "\t" << datetask;
                    flag = true;
                }

                if (comparisonOperator == "<=" && ((day + month * 31 + year * 365) >= (std::stoi(datetask.toStdString().substr(6, 4)) * 365 + std::stoi(datetask.toStdString().substr(3, 2)) * 31 + std::stoi(datetask.toStdString().substr(0, 2)))))
                {
                    qDebug() << id << " " << nametask << "\t" << descriptiontask << "\t" << datetask;
                    flag = true;
                }

                if (comparisonOperator == ">=" && ((day + month * 31 + year * 365) <= (std::stoi(datetask.toStdString().substr(6, 4)) * 365 + std::stoi(datetask.toStdString().substr(3, 2)) * 31 + std::stoi(datetask.toStdString().substr(0, 2)))))
                {
                    qDebug() << id << " " << nametask << "\t" << descriptiontask << "\t" << datetask;
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
    }
}
