//
// Created by anthony on 12/10/16.
//

#include "CacheManager.h"

std::unique_ptr<CacheManager> CacheManager::getInstance() {
  if(instance== nullptr){
    instance=new CacheManager();
  }
  return instance;
}

std::vector<Key>
CacheManager::isCached(std::vector<Key> &keys) {
  std::vector<Key> cachedKeys;
  return cachedKeys;
}


