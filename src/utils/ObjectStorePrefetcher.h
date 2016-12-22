//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_OBJECTSTOREPREFETCHER_H
#define IRIS_OBJECTSTOREPREFETCHER_H


#include "AbstractPrefetcher.h"
#include "../constants.h"
#include "../object_stores/HyperdexClient.h"
#include "../object_stores/ObjectStoreFactory.h"
#include "../mapper/MapperFactory.h"
#include "CacheManager.h"
#include <vector>

class ObjectStorePrefetcher: public AbstractPrefetcher{
private:
  std::unique_ptr<ObjectStoreFactory> objectStoreFactory=ObjectStoreFactory::getInstance();
  std::unique_ptr<CacheManager> cacheManager=CacheManager::getInstance();
  std::unique_ptr<MapperFactory> mapperFactory=MapperFactory::getInstance();;
  int engine(const char * fileName, size_t &fileOffset, size_t &operationSize,int prefetchingMode);
public:
  int fetch(const char *fileName, size_t fileOffset, size_t operationSize);
};


#endif //IRIS_OBJECTSTOREPREFETCHER_H
