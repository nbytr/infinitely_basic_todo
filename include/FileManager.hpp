#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <fstream>
#include <functional>
#include <sstream>

#include "TodoList.hpp"

using NameList = std::vector<std::string>;

class FileManager
{
public:
  FileManager();

  bool isFirstLaunch() const;
  bool doesTodoListExist(const std::string& name) const;
  bool doesTodoListExist(int listIndex);

  NameList& obtainAllTodoListNames();

  std::unique_ptr<TodoList> openTodoList(int listIndex);

  bool createList(const std::string& name);
  bool deleteList(int listIndex);
private:
  // Where user data is stored, set in constructor based on OS.
  std::string dataPath;

  NameList cachedTodoListNames;
  bool cacheValid = false;
};

#endif
