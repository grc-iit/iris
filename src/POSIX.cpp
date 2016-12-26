/******************************************************************************
*include files
******************************************************************************/
#include <cstring>
#include <algorithm>
#include <iostream>
#include "POSIX.h"
#include "utils/Buffer.h"
/******************************************************************************
*Interface operations
******************************************************************************/
/******************************************************************************
*fopen
******************************************************************************/
FILE *iris::fopen(const char *filename, const char *mode) {
#ifdef DEBUG
  std::cout << "Inside fopen start" << std::endl;
#endif/*DEBUG*/
  auto apiInstance = API::getInstance();
  auto posixMetadataManager = std::static_pointer_cast<POSIXMetadataManager>
      (apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER));

  /*Check if the filename is longer than allowed (<256)*/
  if(std::strlen(filename) > MAX_FILENAME_LENGTH){
    fprintf(stderr, "ERROR! File name too long!\n");
    return NULL;
  }
  /*First check if the file already exists and if it is opened*/
  FILE* fh;

  if(posixMetadataManager->checkIfFileExists(filename)){
    if(posixMetadataManager->checkIfFileIsOpen(filename)) return NULL;
    fh = fmemopen(NULL, FILE_BUFFER_CAPACITY, mode);
    if (fh == NULL){
      fprintf(stderr, "fopen() error: %s\n", strerror(errno));
      return NULL;
    }
    posixMetadataManager->updateMetadataOnOpen(fh, filename, mode);
  }
  else{
    fh = fmemopen(NULL, FILE_BUFFER_CAPACITY, mode);
    if (fh == NULL){
      fprintf(stderr, "fmemopen() error: %s\n", strerror(errno));
      return NULL;
    }
    posixMetadataManager->createMetadata(fh, filename, mode);
  }
#ifdef DEBUG
  std::cout << "Inside fopen end" << std::endl;
#endif/*DEBUG*/
  return fh;
}

/******************************************************************************
*fclose
******************************************************************************/
int iris::fclose(FILE *stream) {
  auto apiInstance = API::getInstance();
  auto posixMetadataManager = std::static_pointer_cast<POSIXMetadataManager>
      (apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER));

  const char * filename = posixMetadataManager->getFilename(stream);
  if (!posixMetadataManager->checkIfFileIsOpen(filename)) return -1;
  else {
    std::fclose(stream);
    posixMetadataManager->updateMetadataOnClose(stream, filename);
  }
#ifdef DEBUG
  std::cout << "Inside fclose end" << std::endl;
#endif/*DEBUG*/
  return 0;
}

/******************************************************************************
*fseek
******************************************************************************/
int iris::fseek(FILE *stream, long int offset, int origin) {
  auto apiInstance = API::getInstance();
  auto posixMetadataManager = std::static_pointer_cast<POSIXMetadataManager>
      (apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER));
  posixMetadataManager->updateFpPosition(stream, offset, origin);
  return 0;
}

/******************************************************************************
*fread
******************************************************************************/
size_t iris::fread(void *ptr, std::size_t size, std::size_t count, FILE *stream) {
  auto operationSize = size*count;
  if(operationSize == 0) return 0;

  auto apiInstance = API::getInstance();
  auto posixMetadataManager = std::static_pointer_cast<POSIXMetadataManager>
      (apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER));
  auto posixMapper = std::static_pointer_cast<POSIXMapper>
          (apiInstance->getMapperFactory()->getMapper(POSIX_MAPPER));
  auto cacheManager = apiInstance->getCacheManager();
  auto objectStorePrefetcher = std::static_pointer_cast<ObjectStorePrefetcher>
          (apiInstance->getPrefetcherFactory()->getPrefetcher(OBJECTSTORE_PREFETCHER));
  auto objectStoreClient = std::static_pointer_cast<HyperdexClient>
          (apiInstance->getObjectStoreFactory()->getObjectStore(HYPERDEX_CLIENT));


  const char * filename = posixMetadataManager->getFilename(stream);
  long int fileOffset = posixMetadataManager->getFpPosition(stream);
  auto filesize = posixMetadataManager->getFilesize(filename);
  auto keys = posixMapper->generateKeys(filename, fileOffset, operationSize);

  Buffer buffer = Buffer(ptr);
  size_t bufferIndex = 0;
  for (auto&& key : keys) {
    auto originalKeySize = key.size;
    if(cacheManager->isCached(key) == NO_DATA_FOUND){
      printf("Before get!!!! Key: %s\n", key.name);
      objectStoreClient->get(key);
    }
    buffer.update(key.data,bufferIndex,originalKeySize);
    bufferIndex+=originalKeySize;
  }
#ifdef DEBUG
  std::printf("Reading Data %-30s \n", ptr );
#endif
  objectStorePrefetcher->fetch(filename, fileOffset, operationSize, filesize);
  posixMetadataManager->updateMetadataOnRead(stream, operationSize);
#ifdef DEBUG
  std::cout << "Inside fread end" << std::endl;
#endif/*DEBUG*/
  return operationSize;
}
/******************************************************************************
*fwrite
******************************************************************************/
size_t iris::fwrite(const void *ptr, size_t size, size_t count, FILE *stream) {
  auto operationSize = size * count;
  if(operationSize == 0) return 0;

  auto apiInstance = API::getInstance();
  auto posixMetadataManager = std::static_pointer_cast<POSIXMetadataManager>
      (apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER));
  auto posixMapper = std::static_pointer_cast<POSIXMapper>
          (apiInstance->getMapperFactory()->getMapper(POSIX_MAPPER));
  auto cacheManager = apiInstance->getCacheManager();
  auto objectStoreClient = std::static_pointer_cast<HyperdexClient>
          (apiInstance->getObjectStoreFactory()->getObjectStore(HYPERDEX_CLIENT));

  const char *filename = posixMetadataManager->getFilename(stream);
  if(!posixMetadataManager->checkIfFileIsOpen(filename)) return 0;

  long int fileOffset = posixMetadataManager->getFpPosition(stream);

  auto keys = posixMapper->generateKeys(filename, fileOffset, operationSize);
  std::size_t bufferIndex = 0;
  for (auto &&key : keys) {
    key.data=malloc(key.size);
    memcpy(key.data,(char*)ptr + bufferIndex,key.size);
    objectStoreClient->put(key);
    cacheManager->addToCache(key);
    bufferIndex += key.size;
  }
  posixMetadataManager->updateMetadataOnWrite(stream, operationSize);
#ifdef DEBUG
  std::cout << "Inside fwrite end" << std::endl;
#endif/*DEBUG*/
  return operationSize;
}
