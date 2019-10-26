/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
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




