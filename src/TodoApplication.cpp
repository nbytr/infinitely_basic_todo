#include "TodoApplication.hpp"

int TodoApplication::run()
{
  std::cout << "Infinitely BASIC TODO\n"
            << "---------------------\n";

  if (fileManager.isFirstLaunch())
  {
    std::cout << "This is your first launch of the application, the\n"
              << "program works like a command-line interface, at any\n"
              << "point, type help to re-output the message below:\n";

    printHelpCommand();
  }

  isRunning = true;
  std::string command;

  std::istringstream commandParts;
  std::string firstPart;

  while (isRunning)
  {
    std::cout << "\nistd > ";
    std::getline(std::cin, command);

    commandParts.str(command);
    commandParts.clear();

    commandParts >> firstPart;

    if (firstPart == "help")
    {
      printHelpCommand();
    }
    else if (firstPart == "lists")
    {
      printLists();
    }
    else if (firstPart == "load")
    {
      int listIndex;
      if (!(commandParts >> listIndex))
        std::cout << "Invalid use of load command, proper usage: create <list index>\n";
      else
      {
        if (!loadList(listIndex))
          std::cout << "Failed to load list, maybe the list doesn't exist?\n";
      }
    }
    else if (firstPart == "print")
    {
      if (loadedList)
        printLoadedList();
      else
       std::cout << "You haven't loaded a list, use the load command to do so\n";
    }
    else if (firstPart == "additem")
    {
      if (loadedList)
      {
        std::string item;
        commandParts.ignore(); // ignore the whitespace after additem
        if(!std::getline(commandParts, item))
        {
          std::cout << "Invalid use of the additem command, proper usage: additem <item>\n";
        }
        else
          addItemToLoadedList(item);
      }
      else
        std::cout << "You haven't loaded a list, use the load command to do so\n";
    }
    else if (firstPart == "delitem")
    {
      if (loadedList)
      {
        int listIndex;
        if (!(commandParts >> listIndex))
        {
          std::cout << "Invalid use of delitem command, proper usage: delitem <list index>\n";
        }
        deleteItemFromLoadedList(listIndex);
      }
      else
        std::cout << "You haven't loaded a list, use the load command to do so\n";
    }
    else if (firstPart == "create")
    {
      std::string listName;
      commandParts.ignore(); // ignore the whitespace after the create
      if (!std::getline(commandParts, listName))
      {
        std::cout << "Invalid use of create command, proper usage: create <list name>\n";
      } else
      {
        if(!createList(listName))
          std::cout << "Failed to create list, maybe it already exists?\n";
      }
    }
    else if (firstPart == "delete")
    {
      int listIndex;
      if (!(commandParts >> listIndex))
      {
        std::cout << "Invalid use of delete command, proper usage: delete <list index>\n";
      }
      else
      {
        if (!deleteList(listIndex))
          std::cout << "Failed to delete list, maybe it doesn't exist?\n";
      }
    }
    else if (firstPart == "exit")
    {
      isRunning = false;
    }
    else
    {
      std::cout << "Unrecognized command, type help to see all valid commands";
    }
  }

  return 0;
}

void TodoApplication::printHelpCommand()
{
  std::cout 
    << "help - print this text\n"

    << "lists - print all the todo lists you have created, along"
    << " with your currently loaded one.\n"

    << "create <list name> - create a list with the specified name\n"

    << "load <list index> - load a todo list to read and modify\n"

    << "print - output the currently loaded list's items\n"

    << "additem <item> - add an item to the currently loaded list\n"

    << "delitem <item index> - delete an item from the list\n"

    << "delete <list index> - delete a list\n"

    << "exit - exit the application\n"

    << "\n";
}

void TodoApplication::printLists()
{
  NameList allTodoLists = fileManager.obtainAllTodoListNames();
  if (allTodoLists.empty())
    std::cout << "\nYou have no lists, create one with the create command,"
      << " type help for more details.\n";
  else
  {
    std::cout << "You have currently got: \nList Index | List Name\n"
                                        << "-----------+-------------------------------\n";
    for (auto i = allTodoLists.begin(); i < allTodoLists.end(); ++i)
    {
      std::cout << std::setw(10) << (i - allTodoLists.begin()) << " | " << *i << '\n';
    }
  }

  if (loadedList)
    std::cout << "\nYou have also currently loaded the " << (*loadedList).getName() << '\n';
}

bool TodoApplication::loadList(int listIndex)
{
  if (loadedList) loadedList.reset();
  loadedList = fileManager.openTodoList(listIndex);
  return bool(loadedList);
}

void TodoApplication::printLoadedList()
{
  ItemList& itemLst = loadedList->retrieveItems();

  std::cout << "Item Index | TODO Item\n"
            << "-----------+-----------------------------\n";

  for (auto i = itemLst.begin(); i < itemLst.end(); ++i)
  {
    std::cout << std::setw(10) << (i - itemLst.begin()) << " | " << *i << '\n';
  }

}
void TodoApplication::addItemToLoadedList(const std::string& item)
{
  if (!loadedList->addItem(item))
    std::cout << "Failed to add item.\n";
}

void TodoApplication::deleteItemFromLoadedList(int listIndex)
{
  if (!loadedList->deleteItem(listIndex))
    std::cout << "Failed to delete item.\n";
}

bool TodoApplication::createList(const std::string& name)
{
  return fileManager.createList(name);
}

bool TodoApplication::deleteList(int listIndex)
{
  return fileManager.deleteList(listIndex);
}
