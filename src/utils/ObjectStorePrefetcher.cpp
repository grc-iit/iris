/******************************************************************************
*include files
******************************************************************************/
#include <iostream>
#include <chrono>
#include "../return_codes.h"
#include "ObjectStorePrefetcher.h"
#include "../mapper/POSIXMapper.h"
#include "Timer.h"

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
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
#ifdef DEBUG
  std::cout << "####################  PREFETCHER ################" << std::endl;
#endif/*DEBUG*/
  auto posixMapper = std::static_pointer_cast<POSIXMapper>
      (mapperFactory->getMapper(POSIX_MAPPER));
  int status = engine(fileName, fileOffset, operationSize, fileSize,
                      PREFETCH_MODE);
  if(status == OPERATION_SUCCESSFUL){
    auto keys = posixMapper->generateKeys(fileName, fileOffset, operationSize);
    fetchKeys(keys);
  }
  else return FETCH_FAILED;

#ifdef TIMER
timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int ObjectStorePrefetcher::fetchKeys(std::vector<Key> keys) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  for (auto key:keys) fetchKey(key);
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int ObjectStorePrefetcher::fetchKey(Key key) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  auto objectStoreClient = std::static_pointer_cast<HyperdexClient>
      (objectStoreFactory->getObjectStore(HYPERDEX_CLIENT));
  if(cacheManager->isCached(key) != OPERATION_SUCCESSFUL){
    if(objectStoreClient->get(key) == OPERATION_SUCCESSFUL)
      cacheManager->addToCache(key);
  }
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}
int ObjectStorePrefetcher::engine(const char *fileName, long int &fileOffset,
                                  size_t &operationSize, long int fileSize,
                                  int prefetchingMode) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  switch(prefetchingMode){
    case SEQUENTIAL:
      if(fileOffset+operationSize <= fileSize-operationSize)
        fileOffset += operationSize;
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
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}







