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
#include <memory>
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
#include "mapper/S3Mapper.h"
#include "mapper/MPIIOMapper.h"
#include "mapper/HDF5Mapper.h"
#include "mapper/PNETCDFMapper.h"
#include "metadata_manager/MPIIOMetadataManager.h"
#include "metadata_manager/HDF5MetadataManager.h"
#include "metadata_manager/PNETCDFMetadataManager.h"
#include "metadata_manager/S3MetadataManager.h"


class API{
private:
    static API* instance;
    /*Cache Manager*/
    CacheManager* cacheManager;
    std::unique_ptr<ObjectStorePrefetcher> objectStorePrefetcherInstance;
    std::unique_ptr<MetadataManagerFactory> metadataManagerFactory;
    API(){
        cacheManager=CacheManager::getInstance();
        objectStorePrefetcherInstance = (ObjectStorePrefetcher*)PrefetcherFactory::getInstance()->getPrefetcher(OBJECTSTORE_PREFETCHER);
        metadataManagerFactory=MetadataManagerFactory::getInstance();
    }
public:
    static API* getInstance();

    CacheManager *getCacheManager();

    const std::unique_ptr<ObjectStorePrefetcher> &getObjectStorePrefetcherInstance() const {
        return objectStorePrefetcherInstance;
    }
    const std::unique_ptr<MetadataManagerFactory> &getMetadataManagerFactory() const {
        return metadataManagerFactory;
    }

    virtual ~API() {}
};

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
static MPIIOMetadataManager* mpiioMetadataManager = (MPIIOMetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (MPIIO_METADATA_MANAGER);
static HDF5MetadataManager* hdf5MetadataManager = (HDF5MetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (HDF5_METADATA_MANAGER);
static PNETCDFMetadataManager* pnetcdfMetadataManager = (PNETCDFMetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (PNETCDF_METADATA_MANAGER);
static S3MetadataManager* s3MetadataManager = (S3MetadataManager*)
    MetadataManagerFactory::getInstance()->getMetadataManager
        (S3_METADATA_MANAGER);
/* Mappers*/
static POSIXMapper* posixMapper = (POSIXMapper*) MapperFactory::getInstance()
    ->getMapper(POSIX_MAPPER);
static MPIIOMapper* mpiioMapper = (MPIIOMapper*) MapperFactory::getInstance()
    ->getMapper(MPIIO_MAPPER);
static HDF5Mapper* hdf5Mapper = (HDF5Mapper*) MapperFactory::getInstance()
    ->getMapper(HDF5_MAPPER);
static PNETCDFMapper* pnetcdfMapper = (PNETCDFMapper*)
    MapperFactory::getInstance()->getMapper(PNETCDF_MAPPER);
static S3Mapper* s3Mapper = (S3Mapper*) MapperFactory::getInstance()
    ->getMapper(S3_MAPPER);
#endif //IRIS_ABSTRACTAPI_H
