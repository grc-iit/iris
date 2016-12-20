/******************************************************************************
*include files
******************************************************************************/
#include <cstring>
#include "POSIX.h"
/******************************************************************************
*Interface operations
******************************************************************************/
/******************************************************************************
*fopen
******************************************************************************/
FILE *fopen(const char *filename, const char *mode) {
  std::unique_ptr<API> apiInstance = API::getInstance();
  std::unique_ptr<POSIXMetadataManager> posixMetadataManager =
      (POSIXMetadataManager*)apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER);

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
  return fh;
}

/******************************************************************************
*fclose
******************************************************************************/
int fclose(FILE *stream) {
  std::unique_ptr<API> apiInstance = API::getInstance();
  std::unique_ptr<POSIXMetadataManager> posixMetadataManager =
      (POSIXMetadataManager*)apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER);

  const char * filename = posixMetadataManager->getFilename(stream);
  if (posixMetadataManager->checkIfFileIsOpen(filename)) return -1;
  else {
    std::fclose(stream);
    posixMetadataManager->updateMetadataOnClose(stream, filename);
  }
  return 0;
}

/******************************************************************************
*fseek
******************************************************************************/
int fseek(FILE *stream, long int offset, int origin) {
  std::unique_ptr<API> apiInstance = API::getInstance();
  std::unique_ptr<POSIXMetadataManager> posixMetadataManager =
      (POSIXMetadataManager*)apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER);
  posixMetadataManager->updateFpPosition(stream, offset, origin);
  return 0;
}

/******************************************************************************
*fread
******************************************************************************/
size_t fread(void *ptr, size_t size, size_t count, FILE *stream) {
  std::unique_ptr<API> apiInstance = API::getInstance();
  std::unique_ptr<POSIXMetadataManager> posixMetadataManager =
      (POSIXMetadataManager*)apiInstance->getMetadataManagerFactory()->
          getMetadataManager(POSIX_METADATA_MANAGER);
  std::unique_ptr<POSIXMapper> posixMapper =
      (POSIXMapper*)apiInstance->getMapperFactory()->getMapper(POSIX_MAPPER);
  std::unique_ptr<CacheManager> cacheManager = apiInstance->getCacheManager();
  std::unique_ptr<ObjectStorePrefetcher> objectStorePrefetcher =
      (ObjectStorePrefetcher*)apiInstance->getPrefetcherFactory()->getPrefetcher(OBJECTSTORE_PREFETCHER);


  std::size_t operationSize = size*count;
  const char * filename = posixMetadataManager->getFilename(stream);
  size_t fileOffset = posixMetadataManager->getFpPosition(stream);
  std::vector<Key> getKeys = posixMapper->generateKeys(filename, fileOffset,
                                                    operationSize);
  std::vector<Key> cachedKeys = cacheManager->isCached(getKeys);
  objectStorePrefetcher->fetchKeys(getKeys);
  pass keys to ObjectStoreGetter














  /* Initializing things for the operation*/


  std::size_t num_keys = ((op_size/MAX_OBJ_SIZE)+1);
  char * concat_buf = (char *)malloc(op_size);
  long int file_offset = 0, offset = 0, base_key = 0;
  long int ptr_index = 0;


  /*get the offset from the file pointer according to the stream*/
  std::unordered_map<FILE *, long int>::const_iterator index =
      pointer.find(stream);
  if(index != pointer.end()){
    file_offset = offset = index->second;
    base_key = offset/MAX_OBJ_SIZE;
  }

  /* prepare HyperDex client structs*/
  const struct hyperdex_client_attribute* attributes = 0;
  std::size_t attributes_sz = 0;
  enum hyperdex_client_returncode op_status, loop_status;
  int64_t op_id, loop_id;//todo check if i need to initialize them

  for(std::size_t i =0; i < num_keys; i++){
    /* prepare the key */
    sprintf(keys[i], "%ld", ((base_key+i)*MAX_OBJ_SIZE));
    /*get the keys and copy data to temp buffer*/
    op_id = hyperdex_client_get(kvs_client, space,
                                keys[i], KEY_SIZE,
                                &op_status,
                                &attributes, &attributes_sz);
    loop_id = hyperdex_client_loop(kvs_client, -1, &loop_status);
    if (op_id == loop_id && loop_status == HYPERDEX_CLIENT_SUCCESS) {
      if(offset == ((base_key+i)*MAX_OBJ_SIZE)){
        if(op_size >= MAX_OBJ_SIZE){
          sprintf(&concat_buf[ptr_index], "%.*s", (int)MAX_OBJ_SIZE,
                  attributes->value);
          op_size -= MAX_OBJ_SIZE;
          ptr_index += MAX_OBJ_SIZE;
          offset += MAX_OBJ_SIZE;
        }
        else{
          if(op_size <= attributes->value_sz){
            sprintf(&concat_buf[ptr_index], "%.*s", (int)op_size,
                    attributes->value);
            op_size -= op_size;
            ptr_index += op_size;
            offset += op_size;
          }
          else{
            fprintf(stderr, "Read operation failed! Data don't exist.\n");
            return 0;
          }
        }
      }
      else{
        if(op_size >= MAX_OBJ_SIZE){
          sprintf(&concat_buf[ptr_index], "%.*s",
                  (int)(((base_key+i+1)*MAX_OBJ_SIZE) - offset),
                  &attributes->value[offset]);
          op_size -= (((base_key+i+1)*MAX_OBJ_SIZE) - offset);
          ptr_index += (((base_key+i+1)*MAX_OBJ_SIZE) - offset);
          offset += (((base_key+i+1)*MAX_OBJ_SIZE) - offset);
        }
        else{
          sprintf(&concat_buf[ptr_index], "%.*s", (int)op_size,
                  &attributes->value[offset]);
          op_size -= op_size;
          ptr_index += op_size;
          offset += op_size;
        }
      }
    }
    else{
      fprintf(stderr, "Read operation failed! Data don't exist.\n");
      return 0;
    }
  }
  ptr = concat_buf;
  pointer[index->first] = file_offset + size*count;//move the file pointer
  free(concat_buf);
  return size*count;
}