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
MapperFactory::~MapperFactory() {

}
/******************************************************************************
*Gettters and setters
******************************************************************************/
std::shared_ptr<AbstractMapper> MapperFactory::getMapper(const char *name) {
  std::shared_ptr<AbstractMapper> mapperInstance;
  if(strcmp(name,POSIX_MAPPER)==0){
    mapperInstance = std::shared_ptr<POSIXMapper>();
  }
  else if(strcmp(name,MPIIO_MAPPER)==0){
    mapperInstance = std::shared_ptr<MPIIOMapper>();
  }
  else if(strcmp(name,HDF5_MAPPER)==0){
    mapperInstance = std::shared_ptr<HDF5Mapper>();
  }
  else if(strcmp(name,PNETCDF_MAPPER)==0){
    mapperInstance = std::shared_ptr<PNETCDFMapper>();
  }
  else if(name == S3_MAPPER){
    mapperInstance = std::shared_ptr<S3Mapper>();
  }
  else return nullptr;
  return mapperInstance;
}

