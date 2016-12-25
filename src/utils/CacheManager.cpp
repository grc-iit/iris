#include "CacheManager.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<CacheManager> CacheManager::instance = nullptr;
/******************************************************************************
*Constructor
******************************************************************************/
CacheManager::CacheManager() :cacheCapacity(CACHE_CAPACITY) {
  cacheMap = HIPII();
  lruList = LI();
}
/******************************************************************************
*Destructor
******************************************************************************/
CacheManager::~CacheManager() {}
/******************************************************************************
*Getters and setters
******************************************************************************/
std::shared_ptr<CacheManager> CacheManager::getInstance() {
  if(instance== nullptr){
    instance=std::shared_ptr<CacheManager>(new CacheManager());
  }
  return instance;
}
/******************************************************************************
*Functions
******************************************************************************/
int CacheManager::isCached(Key &key) {
  auto cacheline = cacheMap.find(key.name);
  if(cacheline == cacheMap.end()) return NO_DATA_FOUND;
  refreshLRU(cacheline);
  key.data = cacheline->second.first;
  return OPERATION_SUCCESSFUL;
}

int CacheManager::addDataToBuffer(Key &key) {
  auto cacheline = cacheMap.find(key.name);
  if (cacheline != cacheMap.end()) refreshLRU(cacheline);
  else {
    if (cacheMap.size() == cacheCapacity) {
      cacheMap.erase(lruList.back());
      lruList.pop_back();
    }
    lruList.push_front(key.name);
  }
  cacheMap[key.name] = { key.data, lruList.begin() };
  return OPERATION_SUCCESSFUL;
}

void CacheManager::refreshLRU(std::unordered_map<const char *,
    std::pair<void *, std::_List_iterator<const char *>>>::iterator cacheline) {
  const char * key = cacheline->first;
  lruList.erase(cacheline->second.second);
  lruList.push_front(key);
  cacheline->second.second = lruList.begin();
}


