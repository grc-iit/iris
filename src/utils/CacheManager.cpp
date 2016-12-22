//
// Created by anthony on 12/10/16.
//

#include "CacheManager.h"

std::shared_ptr<CacheManager> CacheManager::getInstance() {
  if(instance== nullptr){
    instance=std::shared_ptr<CacheManager>(new CacheManager());
  }
  return instance;
}

int CacheManager::isCached(Key &key) {
  return OPERATION_SUCCESSUL;
}

int CacheManager::cacheData(Key &key) {
  return OPERATION_SUCCESSUL;
}


