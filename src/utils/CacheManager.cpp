#include <iostream>
#include "CacheManager.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<CacheManager> CacheManager::instance = nullptr;
/******************************************************************************
*Constructor
******************************************************************************/
CacheManager::CacheManager() {
  cacheCapacity = CACHE_CAPACITY;
  cacheMap = HIPII();
  lruList = LI();
}
/******************************************************************************
*Destructor
******************************************************************************/
CacheManager::~CacheManager() {}
/******************************************************************************
*Functions
******************************************************************************/
int CacheManager::isCached(Key &key) {
  auto iterator = cacheMap.find(key.name);
  if(iterator == cacheMap.end()) return NO_DATA_FOUND;
  refreshLRU(iterator);
  key.data = iterator->second.first;
  return OPERATION_SUCCESSFUL;
}

int CacheManager::addToCache(Key &key) {
  auto cacheline = cacheMap.find(key.name);
  if (cacheline != cacheMap.end()){
    refreshLRU(cacheline);
  }
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

void CacheManager::refreshLRU(std::unordered_map<std::string,
    std::pair<void *, std::_List_iterator<std::string>>>::iterator cacheline) {
  std::string key = cacheline->first;
  lruList.erase(cacheline->second.second);
  lruList.push_front(key);
  cacheline->second.second = lruList.begin();
}


