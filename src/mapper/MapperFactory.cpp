/******************************************************************************
*include files
******************************************************************************/
#include "MapperFactory.h"
#include "../constants.h"
#include "POSIXMapper.h"
#include "MPIIOMapper.h"
#include "HDF5Mapper.h"
#include "PNETCDFMapper.h"
#include "S3Mapper.h"

/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<MapperFactory> MapperFactory::instance = nullptr;
/******************************************************************************
*Constructor
******************************************************************************/
MapperFactory::MapperFactory() {}
/******************************************************************************
*Destructor
******************************************************************************/
MapperFactory::~MapperFactory() {}
/******************************************************************************
*Gettters and setters
******************************************************************************/
std::shared_ptr<MapperFactory> MapperFactory::getInstance() {
  if(instance== nullptr){
    instance=std::shared_ptr<MapperFactory>(new MapperFactory());
  }
  return instance;
}
std::shared_ptr<AbstractMapper> MapperFactory::getMapper(const char *name) {
  AbstractMapper* mapperInstance = nullptr;
  if(strcmp(name,POSIX_MAPPER)==0){
    mapperInstance = new POSIXMapper();
  }
  else if(strcmp(name,MPIIO_MAPPER)==0){
    mapperInstance = new MPIIOMapper();
  }
  else if(strcmp(name,HDF5_MAPPER)==0){
    mapperInstance = new HDF5Mapper();
  }
  else if(strcmp(name,PNETCDF_MAPPER)==0){
    mapperInstance = new PNETCDFMapper();
  }
  else if(name == S3_MAPPER){
    mapperInstance = new S3Mapper();
  }
  else return nullptr;
  return std::shared_ptr<AbstractMapper>(mapperInstance);
}

