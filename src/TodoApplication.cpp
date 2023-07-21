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

    std::transform(command.begin(), command.begin(), command.end(), ::tolower);

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
      if (currentList)
        printLoadedList();
      else
       std::cout << "You haven't loaded a list, use the load command to do so\n";
    }
    else if (firstPart == "additem")
    {
      if (currentList)
      {
        std::string item;
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
      if (currentList)
      {
        int listIndex;
        if (!(commandParts >> listIndex))
        {
          std::cout << "Invalid use of delitem command, proper usage: delitem <list index>\n";
        }
        if (!deleteItemFromLoadedList(listIndex))
          std::cout << "Failed to delete item, maybe it doesn't exist?\n";
      }
      else
        std::cout << "You haven't loaded a list, use the load command to do so\n";
    }
    else if (firstPart == "create")
    {
      std::string listName;
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

  if (currentList)
    std::cout << "\nYou have also currently loaded the " << (*currentList).name << '\n';
}

bool TodoApplication::loadList(int listIndex)
{ return true; }
void TodoApplication::printLoadedList()
{}
void TodoApplication::addItemToLoadedList(const std::string& item)
{}
bool TodoApplication::deleteItemFromLoadedList(int listIndex)
{
  return true;
}

bool TodoApplication::createList(const std::string& name)
{
  return fileManager.createList(name);
}

bool TodoApplication::deleteList(int listIndex)
{
  return fileManager.deleteList(listIndex);
}
