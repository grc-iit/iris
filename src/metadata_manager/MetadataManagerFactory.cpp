//
// Created by anthony on 12/10/16.
//

#include "MetadataManagerFactory.h"
#include "../constants.h"
#include "POSIXMetadataManager.h"
#include "MPIIOMetadataManager.h"
#include "HDF5MetadataManager.h"
#include "PNETCDFMetadataManager.h"
#include "S3MetadataManager.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<MetadataManagerFactory> MetadataManagerFactory::instance = nullptr;

MetadataManagerFactory::MetadataManagerFactory() {}
MetadataManagerFactory::~MetadataManagerFactory() {}

std::shared_ptr<MetadataManagerFactory> MetadataManagerFactory::getInstance() {
  if(instance == nullptr){
    instance =
        std::shared_ptr<MetadataManagerFactory>(new MetadataManagerFactory());
  }
  return instance;
}

std::shared_ptr<IrisMetadataManager>
MetadataManagerFactory::getMetadataManager(const char *name) {
  IrisMetadataManager* metadataManagerInstance = nullptr;
  if(strcmp(name,IRIS_METADATA_MANAGER)==0){
    metadataManagerInstance = new IrisMetadataManager();
  }
  else if(strcmp(name,POSIX_METADATA_MANAGER)==0){
    metadataManagerInstance = new POSIXMetadataManager();
  }
  else if(strcmp(name,MPIIO_METADATA_MANAGER)==0){
    metadataManagerInstance = new MPIIOMetadataManager();
  }
  else if(strcmp(name,HDF5_METADATA_MANAGER)==0){
    metadataManagerInstance = new HDF5MetadataManager();
  }
  else if(strcmp(name,PNETCDF_METADATA_MANAGER)==0){
    metadataManagerInstance = new PNETCDFMetadataManager();
  }
  else if(strcmp(name,S3_METADATA_MANAGER)==0){
    metadataManagerInstance = new S3MetadataManager();
  }
  else return nullptr;
  return std::shared_ptr<IrisMetadataManager>(metadataManagerInstance);
}






