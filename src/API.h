/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/*******************************************************************************
* File API.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_API_H
#define IRIS_API_H
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
#include "object_stores/ObjectStoreFactory.h"
#include "file_systems/FileSystemFactory.h"
/******************************************************************************
*Class
******************************************************************************/
class API {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  static std::shared_ptr<API> instance;
  std::shared_ptr<CacheManager> cacheManager;
  std::shared_ptr<PrefetcherFactory> prefetcherFactory;
  std::shared_ptr<MetadataManagerFactory> metadataManagerFactory;
  std::shared_ptr<MapperFactory> mapperFactory;
  std::shared_ptr<ObjectStoreFactory> objectStoreFactory;
  std::shared_ptr<FileSystemFactory> fileSystemFactory;

/******************************************************************************
*Constructors
******************************************************************************/
  API();
public:
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~API();
/******************************************************************************
*Getters and setters
******************************************************************************/
  inline static std::shared_ptr<API> getInstance(){
    return instance== nullptr ? instance=std::shared_ptr<API>(new API())
                              : instance;
  }

  inline std::shared_ptr<CacheManager> getCacheManager(){
    return cacheManager;
  }

  inline std::shared_ptr<PrefetcherFactory> getPrefetcherFactory(){
    return prefetcherFactory;
  }

  inline std::shared_ptr<MetadataManagerFactory> getMetadataManagerFactory() {
    return metadataManagerFactory;
  }

  inline std::shared_ptr<MapperFactory> getMapperFactory(){
    return mapperFactory;
  }

  inline std::shared_ptr<ObjectStoreFactory> getObjectStoreFactory(){
    return objectStoreFactory;
  }

  inline std::shared_ptr<FileSystemFactory> getFileSystemFactory() {
    return fileSystemFactory;
  }

};

#endif //IRIS_API_H
