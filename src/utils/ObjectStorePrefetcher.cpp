//
// Created by anthony on 12/10/16.
//

#include "../return_codes.h"
#include "ObjectStorePrefetcher.h"
#include "../mapper/POSIXMapper.h"

int ObjectStorePrefetcher::fetch(const char *fileName, size_t fileOffset, size_t operationSize) {
  int prefetchingMode = 0;
  std::shared_ptr<POSIXMapper> posixMapper = std::static_pointer_cast<POSIXMapper> (mapperFactory->getMapper(POSIX_MAPPER));
  std::shared_ptr<HyperdexClient> client = std::static_pointer_cast<HyperdexClient> (objectStoreFactory->getObjectStore(HYPERDEX_CLIENT));

  int status = engine(fileName, fileOffset, operationSize, prefetchingMode);
  std::vector<Key> keys = posixMapper->generateKeys(fileName, fileOffset,
                                                    operationSize);
  for (auto&& key:keys) {
    client->get(key);
    cacheManager->cacheData(key);
  }
  return OPERATION_SUCCESSUL;
}

int ObjectStorePrefetcher::engine(const char *fileName, size_t &fileOffset, size_t &operationSize, int prefetchingMode) {
  return OPERATION_SUCCESSUL;
}
