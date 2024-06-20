#ifndef DBWORK_h
#define DBWORK_h

#include <string>
#include <vector>

class DBWork
{
private:
    QSqlDatabase *db;
public:
    DBWork();
    ~DBWork();
    void addTaskFromDB();
    void updateTaskFromDB();
    void deleteTaskFromDB();
    void selectTaskFromDB();
};

#endif