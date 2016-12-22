//
// Created by anthony on 12/10/16.
//

#include "../return_codes.h"
#include "ObjectStorePrefetcher.h"
#include "../mapper/POSIXMapper.h"

int ObjectStorePrefetcher::fetch(const char *fileName, size_t fileOffset, size_t operationSize) {
  int prefetchingMode = 0;
  std::unique_ptr<POSIXMapper> posixMapper =
      (POSIXMapper *) mapperFactory->getMapper(POSIX_MAPPER);
  std::unique_ptr<HyperdexClient> client = (HyperdexClient *) objectStoreFactory->getObjectStore(
      HYPERDEX_CLIENT);
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
