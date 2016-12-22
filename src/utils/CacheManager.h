//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_CACHEMANAGER_H
#define IRIS_CACHEMANAGER_H


#include <memory>
#include <vector>
#include "../constants.h"

class CacheManager {
private:
  static std::shared_ptr<CacheManager> instance;
  CacheManager(){}
public:
  static std::shared_ptr<CacheManager> getInstance();
  int isCached(Key &key);
  int cacheData(Key &key);
};


#endif //IRIS_CACHEMANAGER_H
