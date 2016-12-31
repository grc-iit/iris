#include <iostream>
#include <chrono>
#include "CacheManager.h"
#include "tools/Timer.h"

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
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  auto iterator = cacheMap.find(key.name);
  if(iterator == cacheMap.end()) return NO_DATA_FOUND;
  refreshLRU(iterator);
  key.data = iterator->second.first;
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int CacheManager::addToCache(Key &key) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
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
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int CacheManager::addRangeToCache(std::vector<Key> keys) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  for(auto key:keys){
    addToCache(key);
  }
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}
void CacheManager::refreshLRU(std::unordered_map<std::string,
    std::pair<void *, std::_List_iterator<std::string>>>::iterator cacheline) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  std::string key = cacheline->first;
  lruList.erase(cacheline->second.second);
  lruList.push_front(key);
  cacheline->second.second = lruList.begin();
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
}




