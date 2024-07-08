I present the TodoList project. It implements the storage of tasks in a text document (ToDoList.txt ) and in the database (to connect to the database, you must have PostgreSQL, with the todolist database, a task table with columns: id - with auto-increment, nametask, descriptiontask, datetask with a symbolic data type. The basic database connection settings can be found in the file DBWork.cpp ).

Basic commands: 
1) File or database - selects which file or database you want to work with; 
2) Add - adds tasks; 
3) Update - updates an existing task; 
4) delete - delete a task by ID or name; 
5) select - select tasks by data field; 
6) exit - exit the program and the main commands.
