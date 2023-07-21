#include "FileManager.hpp"
#include <filesystem>
#include <iterator>

FileManager::FileManager()
{
  // Detect the OS and set the data location path accordingly.
#ifdef __unix__
#include <cstdlib>
  std::string username = getenv("USER");
  dataPath = "/home/" + username + "/.local/share/.infinitelybasictodo/";
#elif defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#include <Lmcons.h>
  char username[UNLEN+1];
  DWORD username_len = UNLEN + 1;
  GetUserName(username, &username_len);
  std::string uname = username;

  dataPath = "C:/Users/" + uname + "/.infinitelybasictodo/";
#else
#error Unrecognised operating system
#endif
}

bool FileManager::isFirstLaunch() const
{
  bool result = !(std::filesystem::is_directory(dataPath));

  if (result)
  {
    // Create the directory to stop crashes arising later on
    std::filesystem::create_directories(dataPath);
  }

  return result;
}

bool FileManager::doesTodoListExist(const std::string& name) const
{
  return std::filesystem::exists(dataPath + name + ".lst");
}

std::vector<std::string> FileManager::obtainAllTodoListNames() const
{
  auto initialFile = std::filesystem::directory_iterator(dataPath);

  std::vector<std::string> fileEntries;
  for (const auto& fileEntry : initialFile)
  {
    if (fileEntry.path().extension() == ".lst")
      fileEntries.push_back(fileEntry.path().stem());
  }

  return fileEntries;
}

bool FileManager::createList(const std::string& name) const
{
  if (std::filesystem::exists(dataPath + name + ".lst")) return false;

  std::ofstream f {dataPath + name + ".lst"};
  return bool(f);
}
