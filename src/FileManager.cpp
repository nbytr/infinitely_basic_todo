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

NameList& FileManager::obtainAllTodoListNames()
{
  if (cacheValid) return cachedTodoListNames;

  auto initialFile = std::filesystem::directory_iterator(dataPath);

  NameList fileEntries;
  for (const auto& fileEntry : initialFile)
  {
    if (fileEntry.path().extension() == ".lst")
      fileEntries.push_back(fileEntry.path().stem());
  }

  cachedTodoListNames = std::move(fileEntries);
  cacheValid = true;

  return cachedTodoListNames;
}

bool FileManager::createList(const std::string& name)
{
  if (doesTodoListExist(name)) return false;

  std::ofstream f {dataPath + name + ".lst"};
  if (f)
    cacheValid = false;
  return bool(f);
}

bool FileManager::deleteList(int listIndex)
{
  NameList lst = obtainAllTodoListNames();
  bool r = std::filesystem::remove(dataPath + lst[listIndex] + ".lst");
  if (r)
    cacheValid = false;
  return r;
}

