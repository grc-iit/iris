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
  std::shared_ptr<ObjectStoreFactory> objectStoreFactory;
  std::shared_ptr<CacheManager> cacheManager;
  std::shared_ptr<MapperFactory> mapperFactory;
  int engine(const char * fileName, size_t &fileOffset, size_t &operationSize,int prefetchingMode);
public:
    ObjectStorePrefetcher();
    int fetch(const char *fileName, size_t fileOffset, size_t operationSize);
};


#endif //IRIS_OBJECTSTOREPREFETCHER_H
