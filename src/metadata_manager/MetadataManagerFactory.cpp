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
  if(name == IRIS_METADATA_MANAGER){
    metadataManagerInstance = new IrisMetadataManager();
  }
  else if(name == POSIX_METADATA_MANAGER){
    metadataManagerInstance = new POSIXMetadataManager();
  }
  else if(name == MPIIO_METADATA_MANAGER){
    metadataManagerInstance = new MPIIOMetadataManager();
  }
  else if(name == HDF5_METADATA_MANAGER){
    metadataManagerInstance = new HDF5MetadataManager();
  }
  else if(name == PNETCDF_METADATA_MANAGER){
    metadataManagerInstance = new PNETCDFMetadataManager();
  }
  else if(name == S3_METADATA_MANAGER){
    metadataManagerInstance = new S3MetadataManager();
  }
  else return nullptr;
  return std::shared_ptr<IrisMetadataManager>(metadataManagerInstance);
}






