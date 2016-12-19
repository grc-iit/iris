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
#include "constants.h"
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
/******************************************************************************
*Class
******************************************************************************/
class API{
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  static std::unique_ptr<API> instance;
  std::unique_ptr<CacheManager> cacheManager;
  std::unique_ptr<PrefetcherFactory> prefetcherFactory;
  std::unique_ptr<MetadataManagerFactory> metadataManagerFactory;
  std::unique_ptr<MapperFactory> mapperFactory;
/******************************************************************************
*Constructor
******************************************************************************/
  API();
public:
/******************************************************************************
*Getters and setters
******************************************************************************/
  static std::unique_ptr<API> getInstance();

  std::unique_ptr<CacheManager> getCacheManager() {
    return cacheManager;
  }

  std::unique_ptr<PrefetcherFactory> getPrefetcherFactory() {
    return prefetcherFactory;
  }
  std::unique_ptr<MetadataManagerFactory> getMetadataManagerFactory() {
    return metadataManagerFactory;
  }
  std::unique_ptr<MapperFactory> getMapperFactory() {
    return mapperFactory;
  }
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~API() {}
};

#endif //IRIS_ABSTRACTAPI_H
