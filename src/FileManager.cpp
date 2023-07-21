#include "FileManager.hpp"
#include <filesystem>
#include <iterator>

FileManager::FileManager()
{
  // Detect the OS and set the data location path accordingly.
#ifdef __unix__
  dataPath = "~/local/share/.infinitelybasictodo/";
#elif defined(_WIN32) || defined(WIN32)
  dataPath = "%userprofile%/.infinitelybasictodo/";
#else
#error Unrecognised operating system
#endif
}

bool FileManager::isFirstLaunch() const
{
  return !(std::filesystem::is_directory(dataPath));
}

bool FileManager::doesTodoListExist(const std::string& name) const
{
  return std::filesystem::exists(dataPath + name + ".lst");
}


