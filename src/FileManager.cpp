#include "FileManager.hpp"
#include "TodoList.hpp"
#include <filesystem>
#include <iterator>
#include <memory>

std::string calculateDataPath()
{
  std::string dp;
  // Detect the OS and set the data location path accordingly.
#ifdef __unix__
#include <cstdlib>
  std::string username = getenv("USER");
  dp = "/home/" + username + "/.local/share/.infinitelybasictodo/";
#elif defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#include <Lmcons.h>
  char username[UNLEN+1];
  DWORD username_len = UNLEN + 1;
  GetUserName(username, &username_len);
  std::string uname = username;

  dp = "C:/Users/" + uname + "/.infinitelybasictodo/";
#else
#error Unrecognised operating system
#endif

  return dp;

}
FileManager::FileManager()
  : dataPath {calculateDataPath()}, cachedTodoListNames {NameList{},
    std::function<NameList ()>( [&] () -> NameList {
    auto initialFile = std::filesystem::directory_iterator(dataPath);

    NameList fileEntries;
    for (const auto& fileEntry : initialFile)
    {
      if (fileEntry.path().extension() == ".lst")
        fileEntries.push_back(fileEntry.path().stem());
    }

    return std::move(fileEntries);
  })} {}

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

bool FileManager::doesTodoListExist(int listIndex)
{
  return (listIndex >= 0 && listIndex < obtainAllTodoListNames().size());
}

NameList& FileManager::obtainAllTodoListNames()
{
  return cachedTodoListNames.getRef();
}

bool FileManager::createList(const std::string& name)
{
  if (doesTodoListExist(name)) return false;

  std::ofstream f {dataPath + name + ".lst"};
  if (f)
    cachedTodoListNames.invalidateCache();
  return bool(f);
}

bool FileManager::deleteList(int listIndex)
{
  if (!doesTodoListExist(listIndex)) return false;

  NameList lst = obtainAllTodoListNames();
  bool r = std::filesystem::remove(dataPath + lst[listIndex] + ".lst");
  if (r)
    cachedTodoListNames.invalidateCache();
  return r;
}

std::unique_ptr<TodoList> FileManager::openTodoList(int listIndex)
{
  if (!doesTodoListExist(listIndex))
    return std::unique_ptr<TodoList> {nullptr};

  std::unique_ptr<TodoList> tdList = std::make_unique<TodoList>(
      std::filesystem::path(dataPath + obtainAllTodoListNames()[listIndex] + ".lst")
  );

  return tdList;
}
