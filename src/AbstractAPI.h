//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_ABSTRACTAPI_H
#define IRIS_ABSTRACTAPI_H

#include "utils/AbstractPrefetcher.h"
#include "utils/PrefetcherFactory.h"
#include "Constants.h"
#include "utils/CacheManager.h"
#include "utils/ObjectStorePrefetcher.h"
#include "utils/FileSystemPrefetcher.h"

static CacheManager* cacheManager=CacheManager::getInstance();
static ObjectStorePrefetcher* objectStorePrefetcherInstance=(ObjectStorePrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(OBJECTSTORE_PREFETCHER);
static FileSystemPrefetcher* fileSystemPrefetcherInstance=(FileSystemPrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(FILESYSTEM_PREFETCHER);


#endif //IRIS_ABSTRACTAPI_H
