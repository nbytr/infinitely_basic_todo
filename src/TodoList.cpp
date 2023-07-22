#include "TodoList.hpp"
#include <stdexcept>

TodoList::TodoList(const std::string& fileName)
  : name {fileName}, items {}
{
  file =
    std::fstream {fileName,
      std::ios_base::in | std::ios_base::out
        | std::ios_base::app };

  if (!file)
  {
    throw std::runtime_error("Failed to open Todo List that should exist.");
  }

  std::string line;
  while (file)
  {
    std::getline(file, line);
    if (!line.empty())
      items.push_back(line);
  }

  file.clear();
}

ItemList& TodoList::retrieveItems()
{
  return items;
}

bool TodoList::addItem(const std::string& item)
{
  items.push_back(item);

  file.seekg(0, std::ios::end);

  file << item << '\n';

  return bool(file);
}
