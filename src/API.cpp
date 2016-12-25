#include "API.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<API> API::instance = nullptr;
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
*Destructor
******************************************************************************/
API::~API() {}
/******************************************************************************
*Getters and setters
******************************************************************************/
std::shared_ptr<API> API::getInstance() {
  if(API::instance== nullptr){
    API::instance=std::shared_ptr<API>(new API());
  }
  return API::instance;
}











