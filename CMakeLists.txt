cmake_minimum_required(VERSION 3.16)
project(ToDoList)
set(CMAKE_CXX_STANDARD 17)

set(SRC 
    main.cpp)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC})