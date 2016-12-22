//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_CACHEMANAGER_H
#define IRIS_CACHEMANAGER_H


#include <bits/unique_ptr.h>
#include <vector>
#include "../constants.h"

class CacheManager {
private:
  static std::unique_ptr<CacheManager> instance;
  CacheManager(){

  }
public:
  static std::unique_ptr<CacheManager> getInstance();
  int isCached(Key &key);
  int cacheData(Key &key);
};


#endif //IRIS_CACHEMANAGER_H
