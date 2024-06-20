cmake_minimum_required(VERSION 3.16)
project(ToDoList)
set(CMAKE_CXX_STANDARD 17)

set(SRC 
    main.cpp
    utils.cpp
    ToDoList.cpp
    DBWork.cpp
    )

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Network)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Sql)