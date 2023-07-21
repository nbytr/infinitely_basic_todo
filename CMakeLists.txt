cmake_minimum_required(VERSION 3.2.0)

project(infinitely_basic_todo)

set(SOURCES
  src/main.cpp
  src/TodoApplication.cpp
  src/FileManager.cpp
  src/TodoList.cpp
)

add_executable(infinitely_basic_todo ${SOURCES})

target_include_directories(
  infinitely_basic_todo PRIVATE ${PROJECT_SOURCE_DIR}/include)
