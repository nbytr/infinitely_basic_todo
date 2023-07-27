#include <functional>

template <typename Resource>
class CachedResult
{
public:
  CachedResult<Resource> (Resource defaultValue, std::function<Resource ()> f)
    : source {f}, cachedResource {defaultValue}, cacheValid {false} {}

  Resource get()
  {
    if (cacheValid) return cachedResource;

    cacheValid = true;
    cachedResource = source();
    return cachedResource;
  }

  Resource& getRef()
  {
    if (cacheValid) return cachedResource;
    
    cacheValid = true;
    cachedResource = source();
    return cachedResource;
  }

  void invalidateCache()
  {
    cacheValid = false;
  }

private:
  Resource cachedResource;
  bool cacheValid;
  std::function<Resource ()> source;
};
