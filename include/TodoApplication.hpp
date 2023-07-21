#ifndef TODO_APPLICATION_HPP
#define TODO_APPLICATION_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "FileManager.hpp"
#include "TodoList.hpp"

class TodoApplication
{
public:
  TodoApplication() : isRunning {false} {}
  int run();

  std::unique_ptr<TodoList> currentList = nullptr;

  // Commands
  void printHelpCommand();
  void printLists();
  void printLoadedList();
  bool createList(const std::string& name);

private:
  bool isRunning;

  FileManager fileManager;
};

#endif
