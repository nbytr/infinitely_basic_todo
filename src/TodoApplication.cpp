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
  std::cout << "\nHELP command output:\n"

    << "lists - print all the todo lists you have created, along"
    << " with your currently loaded one.\n"

    << "load <list name> - load a todo list to read and modify\n"

    << "print - output the currently loaded list's items\n"

    << "exit - exit the application\n"

    << "\n";
}

void TodoApplication::printLists() {}
void TodoApplication::printLoadedList() {}
