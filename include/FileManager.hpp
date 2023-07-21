#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <fstream>

#include "TodoList.hpp"

using NameList = std::vector<std::string>;

class FileManager
{
public:
  FileManager();

  bool isFirstLaunch() const;
  bool doesTodoListExist(const std::string& name) const;

  NameList obtainAllTodoListNames() const;

  std::unique_ptr<TodoList> openTodoList(const std::string& name) const;

  bool createList(const std::string& name) const;
  bool deleteList(int listIndex) const;
private:
  // Where user data is stored, set in constructor based on OS.
  std::string dataPath;
};

#endif
