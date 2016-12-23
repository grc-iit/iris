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

MetadataManagerFactory::MetadataManagerFactory() {
  metadataManagerMap = std::unordered_map<const char*, std::shared_ptr<IrisMetadataManager>>();
}
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
  std::unordered_map<const char*, std::shared_ptr<IrisMetadataManager>>::const_iterator iter =
          metadataManagerMap.find(name);
  if(iter != metadataManagerMap.end()){
    return iter->second;
  }
  else {
    IrisMetadataManager *metadataManagerInstance = nullptr;
    if (strcmp(name, IRIS_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new IrisMetadataManager();
    } else if (strcmp(name, POSIX_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new POSIXMetadataManager();
    } else if (strcmp(name, MPIIO_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new MPIIOMetadataManager();
    } else if (strcmp(name, HDF5_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new HDF5MetadataManager();
    } else if (strcmp(name, PNETCDF_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new PNETCDFMetadataManager();
    } else if (strcmp(name, S3_METADATA_MANAGER) == 0) {
      metadataManagerInstance = new S3MetadataManager();
    } else return nullptr;
    std::shared_ptr<IrisMetadataManager> pointerMetadataManagerInstance=std::shared_ptr<IrisMetadataManager>(metadataManagerInstance);
    metadataManagerMap.emplace(name,pointerMetadataManagerInstance);
    return pointerMetadataManagerInstance;
  }
}






