#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>

#include "TodoList.hpp"

class FileManager
{
public:
  FileManager();

  bool isFirstLaunch() const;
  bool doesTodoListExist(const std::string& name) const;

  std::vector<std::string> obtainAllTodoListNames() const;

  std::unique_ptr<TodoList> openTodoList(const std::string& name) const;

private:
  // Where user data is stored, set in constructor based on OS.
  std::string dataPath;
};

#endif
