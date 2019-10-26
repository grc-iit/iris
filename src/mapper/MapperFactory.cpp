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
  else if(strcmp(name,S3_MAPPER)==0){
    mapperInstance = S3Mapper::getInstance();
  }
  else return nullptr;
  return mapperInstance;
}

