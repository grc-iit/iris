#include "API.h"
/******************************************************************************
*Constructor
******************************************************************************/
API::API() {
  cacheManager = CacheManager::getInstance();
  prefetcherFactory = PrefetcherFactory::getInstance();
  metadataManagerFactory = MetadataManagerFactory::getInstance();
  mapperFactory = MapperFactory::getInstance();
  objectStoreFactory=ObjectStoreFactory::getInstance();
}
/******************************************************************************
*Getters and setters
******************************************************************************/
static std::unique_ptr<API> API::getInstance() {
  if(instance== nullptr){
    instance=new API();
  }
  return instance;
}









