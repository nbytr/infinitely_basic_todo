#ifndef TODO_LIST_HPP
#define TODO_LIST_HPP

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ItemList = std::vector<std::string>;

// Will handle an individual list file
class TodoList
{
public:
  TodoList(std::filesystem::path fP);

  ItemList& retrieveItems();

  bool addItem(const std::string& item);
  bool deleteItem(int listIndex);

  std::string getName() const
  {
    return filePath.stem();
  }

private:
  std::filesystem::path filePath;
  std::fstream file;
  ItemList items;
};

#endif
