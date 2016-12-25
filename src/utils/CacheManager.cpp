#include "CacheManager.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<CacheManager> CacheManager::instance = nullptr;
/******************************************************************************
*Constructor
******************************************************************************/
CacheManager::CacheManager() {}
/******************************************************************************
*Destructor
******************************************************************************/
CacheManager::~CacheManager() {}
/******************************************************************************
*Getters and setters
******************************************************************************/
std::shared_ptr<CacheManager> CacheManager::getInstance() {
  if(instance== nullptr){
    instance=std::shared_ptr<CacheManager>(new CacheManager());
  }
  return instance;
}
/******************************************************************************
*Functions
******************************************************************************/
int CacheManager::isCached(Key &key) {
  return CACHE_MANAGER_NO_DATA_FOUND;
}

int CacheManager::addToBuffer(Key &key) {
  return OPERATION_SUCCESSUL;
}


