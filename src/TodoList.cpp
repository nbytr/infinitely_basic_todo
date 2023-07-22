#include "TodoList.hpp"
#include <stdexcept>

TodoList::TodoList(std::filesystem::path fp)
  : filePath {fp}, items {}
{
  file =
    std::fstream { filePath,
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

bool TodoList::deleteItem(int listIndex)
{
  if (listIndex < 0 || listIndex >= items.size()) return false;

  items.erase(items.begin() + (listIndex));

  std::cout << "Items size: " << items.size() << '\n';

  // re-open the file in truncated mode to delete everything
  // and write from the beginning

  file = std::fstream {filePath,
    std::ios_base::in | std::ios_base::out
    | std::ios::trunc };

  if (items.size() == 0)
    std::filesystem::remove(filePath);

  for (auto item : items)
  {
    std::cout << "writing " << item <<'\n';
    file << item << '\n';
  }

  return bool(file);
}
