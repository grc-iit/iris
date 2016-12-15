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
#include "metadata_manager/POSIXMetadataManager.h"
#include "metadata_manager/MetadataManagerFactory.h"

static CacheManager* cacheManager=CacheManager::getInstance();
static ObjectStorePrefetcher* objectStorePrefetcherInstance=(ObjectStorePrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(OBJECTSTORE_PREFETCHER);
static FileSystemPrefetcher* fileSystemPrefetcherInstance=(FileSystemPrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(FILESYSTEM_PREFETCHER);
static POSIXMetadataManager* posixMetadataManager = (POSIXMetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (POSIX_METADATA_MANAGER);

#endif //IRIS_ABSTRACTAPI_H
