#ifndef UTILS_h
#define UTILS_h
#include <string>
#include <vector>

void readFile(std::vector<std::string> &arrayToDoListTasks);
void writeFile(std::vector<std::string> &arrayToDoListTasks);
std::string setCheckedDate();

#endif