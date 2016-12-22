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

int CacheManager::isCached(Key &key) {
  return OPERATION_SUCCESSUL;
}

int CacheManager::cacheData(Key &key) {
  return OPERATION_SUCCESSUL;
}


