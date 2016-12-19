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
std::unique_ptr<MapperFactory> MapperFactory::getInstance() {
  if(instance== nullptr){
    instance=new MapperFactory();
  }
  return instance;
}
std::unique_ptr<AbstractMapper> MapperFactory::getMapper(const char *name) {
  std::unique_ptr<AbstractMapper> mapperInstance = nullptr;
  if(name == POSIX_MAPPER){
    mapperInstance = new POSIXMapper();
  }
  else if(name == MPIIO_MAPPER){
    mapperInstance = new MPIIOMapper();
  }
  else if(name == HDF5_MAPPER){
    mapperInstance = new HDF5Mapper();
  }
  else if(name == PNETCDF_MAPPER){
    mapperInstance = new PNETCDFMapper();
  }
  else if(name == S3_MAPPER){
    mapperInstance = new S3Mapper();
  }
  else return nullptr;
  return mapperInstance;
}
