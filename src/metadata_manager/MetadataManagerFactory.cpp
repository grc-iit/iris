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


MetadataManagerFactory::MetadataManagerFactory() {}
MetadataManagerFactory::~MetadataManagerFactory() {}

std::unique_ptr<MetadataManagerFactory> MetadataManagerFactory::getInstance() {
  if(instance == nullptr){
    instance = new MetadataManagerFactory();
  }
  return instance;
}

std::unique_ptr<IrisMetadataManager>
MetadataManagerFactory::getMetadataManager(const char *name) {
  std::unique_ptr<IrisMetadataManager> metadataManagerInstance = nullptr;
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
  return metadataManagerInstance;
}




