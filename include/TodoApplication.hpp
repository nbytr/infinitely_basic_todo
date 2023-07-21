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
  bool loadList(int listIndex);
  void printLoadedList();
  void addItemToLoadedList(const std::string& item);
  bool deleteItemFromLoadedList(int listIndex);
  bool createList(const std::string& name);
  bool deleteList(int listIndex);

private:
  bool isRunning;

  FileManager fileManager;
};

#endif
