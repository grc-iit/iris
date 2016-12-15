/*******************************************************************************
* File AbstractAPI.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_ABSTRACTAPI_H
#define IRIS_ABSTRACTAPI_H
/******************************************************************************
*include files
******************************************************************************/
#include "utils/AbstractPrefetcher.h"
#include "utils/PrefetcherFactory.h"
#include "Constants.h"
#include "utils/CacheManager.h"
#include "utils/ObjectStorePrefetcher.h"
#include "utils/FileSystemPrefetcher.h"
#include "metadata_manager/POSIXMetadataManager.h"
#include "metadata_manager/MetadataManagerFactory.h"
#include "metadata_manager/IrisMetadataManager.h"
#include "mapper/POSIXMapper.h"
#include "mapper/MapperFactory.h"
/******************************************************************************
*Initializing various library components
******************************************************************************/
/*Cache Manager*/
static CacheManager* cacheManager=CacheManager::getInstance();
/*Prefetchers*/
static ObjectStorePrefetcher* objectStorePrefetcherInstance=(ObjectStorePrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(OBJECTSTORE_PREFETCHER);
static FileSystemPrefetcher* fileSystemPrefetcherInstance=(FileSystemPrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(FILESYSTEM_PREFETCHER);
/*Metadata Managers*/
static IrisMetadataManager* irisMetadataManager = (IrisMetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (IRIS_METADATA_MANAGER);
static POSIXMetadataManager* posixMetadataManager = (POSIXMetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (POSIX_METADATA_MANAGER);
/* Mappers*/
static POSIXMapper* posixMapper = (POSIXMapper*) MapperFactory::getInstance()
    ->getMapper(POSIX_MAPPER);
#endif //IRIS_ABSTRACTAPI_H
