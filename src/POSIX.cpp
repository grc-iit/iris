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
  std::shared_ptr<API> apiInstance = API::getInstance();
  std::shared_ptr<POSIXMetadataManager> posixMetadataManager =
      std::static_pointer_cast<POSIXMetadataManager>(apiInstance->
          getMetadataManagerFactory()->getMetadataManager(POSIX_METADATA_MANAGER));

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
  std::shared_ptr<API> apiInstance = API::getInstance();
  std::shared_ptr<POSIXMetadataManager> posixMetadataManager =
      std::static_pointer_cast<POSIXMetadataManager>(apiInstance->
          getMetadataManagerFactory()->getMetadataManager(POSIX_METADATA_MANAGER));

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
  std::shared_ptr<API> apiInstance = API::getInstance();
  std::shared_ptr<POSIXMetadataManager> posixMetadataManager =
      std::static_pointer_cast<POSIXMetadataManager>(apiInstance->
          getMetadataManagerFactory()->getMetadataManager(POSIX_METADATA_MANAGER));
  posixMetadataManager->updateFpPosition(stream, offset, origin);
  return 0;
}

/******************************************************************************
*fread
******************************************************************************/
size_t iris::fread(void *ptr, std::size_t size, std::size_t count, FILE *stream) {
  std::shared_ptr<API> apiInstance = API::getInstance();
  std::shared_ptr<POSIXMetadataManager> posixMetadataManager =
      std::static_pointer_cast<POSIXMetadataManager>(apiInstance->
          getMetadataManagerFactory()->getMetadataManager(POSIX_METADATA_MANAGER));
  std::shared_ptr<POSIXMapper> posixMapper =
      std::static_pointer_cast<POSIXMapper>(apiInstance->getMapperFactory()->getMapper(POSIX_MAPPER));
  std::shared_ptr<CacheManager> cacheManager = apiInstance->getCacheManager();
  std::shared_ptr<ObjectStorePrefetcher> objectStorePrefetcher =
      std::static_pointer_cast<ObjectStorePrefetcher>(apiInstance->getPrefetcherFactory()->getPrefetcher(OBJECTSTORE_PREFETCHER));
  std::shared_ptr<HyperdexClient> hyperdexClient =
      std::static_pointer_cast<HyperdexClient>(apiInstance->getObjectStoreFactory()->getObjectStore(HYPERDEX_CLIENT));

  std::size_t operationSize = size*count;
  const char * filename = posixMetadataManager->getFilename(stream);
  std::size_t fileOffset = posixMetadataManager->getFpPosition(stream);
  std::vector<Key> keys =
      posixMapper->generateKeys(filename, fileOffset, operationSize);

  Buffer buffer = Buffer(ptr);
  size_t bufferIndex=0;
  for (auto&& key : keys) {
    size_t originalKeySize=key.size;
    if(cacheManager->isCached(key) != OPERATION_SUCCESSUL){
      hyperdexClient->get(key);
    }
    buffer.update(key.data,bufferIndex,originalKeySize);
    bufferIndex+=originalKeySize;
  }
#ifdef DEBUG
  std::printf("Reading Data %-30s \n", ptr );
#endif
  //objectStorePrefetcher->fetch(filename, fileOffset, operationSize);
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
  /*TODO: error checking
   * operation size
   * is fh valid or opened?
   *
   */
  std::cout << "IRIS FWRITE HERE!!!!!!" << std::endl;
  std::shared_ptr<API> apiInstance = API::getInstance();
  std::shared_ptr<POSIXMetadataManager> posixMetadataManager =
      std::static_pointer_cast<POSIXMetadataManager>(apiInstance->
          getMetadataManagerFactory()->getMetadataManager(POSIX_METADATA_MANAGER));
  std::shared_ptr<POSIXMapper> posixMapper =
      std::static_pointer_cast<POSIXMapper>(apiInstance->getMapperFactory()->getMapper(POSIX_MAPPER));
  std::shared_ptr<HyperdexClient> hyperdexClient =
      std::static_pointer_cast<HyperdexClient>(apiInstance->getObjectStoreFactory()->getObjectStore(HYPERDEX_CLIENT));

  std::size_t operationSize = size * count;
  const char *filename = posixMetadataManager->getFilename(stream);
  std::size_t fileOffset = posixMetadataManager->getFpPosition(stream);

  std::vector<Key> keys =
      posixMapper->generateKeys(filename, fileOffset, operationSize);
    std::size_t bufferIndex = 0;
  for (auto &&key : keys) {
    key.data=malloc(key.size);
    memcpy(key.data,(char*)ptr + bufferIndex,key.size);
    hyperdexClient->put(key);
    bufferIndex += key.size;
  }
  posixMetadataManager->updateMetadataOnWrite(stream, operationSize);
#ifdef DEBUG
    std::cout << "Inside fwrite end" << std::endl;
#endif/*DEBUG*/
  return operationSize;
}
