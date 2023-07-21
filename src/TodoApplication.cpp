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
    else if (firstPart == "create")
    {
      std::string listName;
      if (!(commandParts >> listName))
      {
        std::cout << "Invalid use of create command, proper usage: create <list name>\n";
      } else
      {
        if(!createList(listName))
          std::cout << "Failed to create list, maybe it already exists?\n";
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
    << "lists - print all the todo lists you have created, along"
    << " with your currently loaded one.\n"

    << "create <list name> - create a list with the specified name\n"

    << "load <list name> - load a todo list to read and modify\n"

    << "print - output the currently loaded list's items\n"

    << "exit - exit the application\n"

    << "\n";
}

void TodoApplication::printLists()
{
  auto allTodoLists = fileManager.obtainAllTodoListNames();
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

void TodoApplication::printLoadedList() {}

bool TodoApplication::createList(const std::string& name)
{
  return fileManager.createList(name);
}
