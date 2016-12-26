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
                                 size_t operationSize, long int fileSize) {
#ifdef DEBUG
  std::cout << "Inside prefetcher start" << std::endl;
#endif/*DEBUG*/
  auto posixMapper = std::static_pointer_cast<POSIXMapper>
          (mapperFactory->getMapper(POSIX_MAPPER));
  auto objectStoreClient = std::static_pointer_cast<HyperdexClient>
          (objectStoreFactory->getObjectStore(HYPERDEX_CLIENT));

  int status = engine(fileName, fileOffset, operationSize, fileSize,
                      PREFETCH_MODE);
  if(status == OPERATION_SUCCESSFUL){
    auto keys = posixMapper->generateKeys(fileName, fileOffset, operationSize);
    for (auto&& key:keys) {
      objectStoreClient->get(key);
      cacheManager->addToCache(key);
    }
  }
  else return FETCH_FAILED;
#ifdef DEBUG
  std::cout << "Inside prefetcher end" << std::endl;
#endif/*DEBUG*/
  return OPERATION_SUCCESSFUL;
}

int ObjectStorePrefetcher::engine(const char *fileName, long int &fileOffset,
                                  size_t &operationSize, long int fileSize,
                                  int prefetchingMode) {
  switch(prefetchingMode){
    case SEQUENTIAL:
      if(fileOffset+operationSize <= fileSize) fileOffset += operationSize;
      else return PREFETCH_ENGINE_FAILED;
      break;
    case STRIDED:

      break;
    case RANDOM:
      fileOffset = operationSize*rand()%(fileSize/operationSize+1);
      if(fileOffset >= fileSize) return PREFETCH_ENGINE_FAILED;
      break;
    case USER_DEFINED:

      break;
    default:
      fprintf(stderr, "Prefetch Mode is no valid!\n");
      return PREFETCH_ENGINE_FAILED;
  }
  return OPERATION_SUCCESSFUL;
}


