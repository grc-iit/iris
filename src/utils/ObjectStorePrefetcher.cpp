/******************************************************************************
*include files
******************************************************************************/
#include <iostream>
#include "../return_codes.h"
#include "ObjectStorePrefetcher.h"
#include "../mapper/POSIXMapper.h"
/******************************************************************************
*Constructor
******************************************************************************/
ObjectStorePrefetcher::ObjectStorePrefetcher() {
  objectStoreFactory=ObjectStoreFactory::getInstance();
  cacheManager=CacheManager::getInstance();
  mapperFactory=MapperFactory::getInstance();
}
/******************************************************************************
*Destructor
******************************************************************************/
ObjectStorePrefetcher::~ObjectStorePrefetcher() {}
/******************************************************************************
*Interface
******************************************************************************/
int ObjectStorePrefetcher::fetch(const char *fileName, long int fileOffset,
                                 size_t operationSize, int prefetchingMode) {
#ifdef DEBUG
  std::cout << "Inside prefetcher start" << std::endl;
#endif/*DEBUG*/
  std::shared_ptr<POSIXMapper> posixMapper =
      std::static_pointer_cast<POSIXMapper>
          (mapperFactory->getMapper(POSIX_MAPPER));
  std::shared_ptr<HyperdexClient> objectStoreClient =
      std::static_pointer_cast<HyperdexClient>
          (objectStoreFactory->getObjectStore(HYPERDEX_CLIENT));

  int status = engine(fileName, fileOffset, operationSize, prefetchingMode);
  std::vector<Key> keys = posixMapper->generateKeys(fileName, fileOffset,
                                                    operationSize);
  for (auto&& key:keys) {
    objectStoreClient->get(key);
    cacheManager->addToBuffer(key);
  }
#ifdef DEBUG
  std::cout << "Inside prefetcher end" << std::endl;
#endif/*DEBUG*/
  return OPERATION_SUCCESSUL;
}

int ObjectStorePrefetcher::engine(const char *fileName, long int &fileOffset,
                                  size_t &operationSize, int prefetchingMode) {
  return OPERATION_SUCCESSUL;
}


