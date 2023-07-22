#ifndef TODO_LIST_HPP
#define TODO_LIST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ItemList = std::vector<std::string>;

// Will handle an individual list file
class TodoList
{
public:
  std::string name;

  TodoList(const std::string& fileName);

  ItemList& retrieveItems();

  bool addItem(const std::string& item);

private:
  std::fstream file;
  ItemList items;
};

#endif
