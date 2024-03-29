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
* File constants.h
*
* Goal: Define various library constants and system parameters
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_CONSTANTS_H
#define IRIS_CONSTANTS_H
/******************************************************************************
*include files
******************************************************************************/
#include <cstring>
#include <sys/types.h>
#include <string>
#include <future>
#include <set>
#include <unordered_map>
#include "return_codes.h"
/******************************************************************************
*Iris library parameters
******************************************************************************/
static const u_int16_t MAX_FILENAME_LENGTH = 256;
static const u_int16_t FILE_BUFFER_CAPACITY = 1;
static const char * POSIX_MODE = "RELAXED"; //"STRICT" - "RELAXED"
static const char * CACHING_MODE = "ON"; // "ON" - "OFF"
static const char * GET_OPERATION = "GET";
static const char * PUT_OPERATION = "PUT";
static const u_int16_t MAX_KEY_LENGTH = 32;
static const size_t MAX_OBJ_SIZE = 128*1024;
static const size_t MAX_VF_SIZE = 100*1024*1024;
static const u_int64_t CACHE_CAPACITY = 1073741824;
static std::future<int> asyncOperation;
/******************************************************************************
*Prefetcher
******************************************************************************/
static const char * FILESYSTEM_PREFETCHER = "FILESYSTEM_PREFETCHER";
static const char * OBJECTSTORE_PREFETCHER = "OBJECTSTORE_PREFETCHER";
typedef enum prefetching_modes{
  SEQUENTIAL    = 0,
  STRIDED       = 1,
  RANDOM        = 2,
  USER_DEFINED  = 3
} prefetch_mode;
static const u_int16_t PREFETCH_MODE = SEQUENTIAL;
/******************************************************************************
*Metadata Manager
******************************************************************************/
static const char * IRIS_METADATA_MANAGER = "IRIS_METADATA_MANAGER";
static const char * POSIX_METADATA_MANAGER = "POSIX_METADATA_MANAGER";
static const char * MPIIO_METADATA_MANAGER = "MPIIO_METADATA_MANAGER";
static const char * HDF5_METADATA_MANAGER = "HDF5_METADATA_MANAGER";
static const char * PNETCDF_METADATA_MANAGER = "PNETCDF_METADATA_MANAGER";
static const char * S3_METADATA_MANAGER = "S3_METADATA_MANAGER";
/******************************************************************************
*Mapper
******************************************************************************/
static const char * POSIX_MAPPER ="POSIX_MAPPER";
static const char * MPIIO_MAPPER ="MPIIO_MAPPER";
static const char * HDF5_MAPPER = "HDF5_MAPPER";
static const char * PNETCDF_MAPPER = "PNETCDF_MAPPER";
static const char * S3_MAPPER = "S3_MAPPER";
static const u_int32_t SEED = 0;
/******************************************************************************
*Object Stores
******************************************************************************/
static const char * HYPERDEX_CLIENT ="HYPERDEX_CLIENT";
static const char * SPACE = "IRIS_KEYSPACE";
static const char * ATTRIBUTE_NAME = "data";
static const char * DESCRIPTION = "space IRIS_KEYSPACE key filename_chunk "
    "attributes data";
static const char * COORDINATOR  = "127.0.0.1";
static const u_int16_t COORDINATOR_PORT = 1982;
/******************************************************************************
*File Systems
******************************************************************************/
static const char * PVFS2_CLIENT = "PVFS2_CLIENT";
static std::string TEMP_LOCATION= "/tmp/files/";
/******************************************************************************
*Key structure
******************************************************************************/
struct Key{
    const char * name;
    std::size_t offset;
    std::size_t size;
    void* data;
};
/******************************************************************************
*Virtual File Structure
******************************************************************************/
class VirtualFile{
private:
  std::string filename;
  FILE* fh;
  long int offset;
  size_t size;
  void * data;
  std::unordered_map<std::string,Key > keys;
  std::unordered_map<std::string,Key > invalidKeys;
  bool filled;
  void * mmappedData;

public:VirtualFile() {
    fh = nullptr;
    offset = 0;
    size = 0;
    keys=std::unordered_map<std::string,Key >();
      invalidKeys=std::unordered_map<std::string,Key >();
    filled=false;
  }

  virtual ~VirtualFile() {}

  void * getMmappedData() {
    return mmappedData;
  }

  void setMmappedData(void *mmappedData) {
    VirtualFile::mmappedData = mmappedData;
  }

  bool isFilled() {
    return filled;
  }

  void setFilled(bool filled) {
    VirtualFile::filled = filled;
  }

  void *getData() {
    return data;
  }

  void setData(void *data) {
    VirtualFile::data = data;
  }

  std::string getFilename() {
    return filename;
  }

  void setFilename(std::string filename) {
    VirtualFile::filename = filename;
  }

  FILE *getFh()  {
    return fh;
  }

  void setFh(FILE *fh) {
    VirtualFile::fh = fh;
  }

  long int getOffset()  {
    return offset;
  }

  void setOffset(long int offset) {
    VirtualFile::offset = offset;
  }

  size_t getSize() {
    return size;
  }

  void setSize(size_t size) {
    VirtualFile::size = size;
  }

  std::unordered_map<std::string,Key > getKeys()  {
    return keys;
  }
    std::unordered_map<std::string,Key > getInvalidKeys()  {
      return invalidKeys;
    }
};

#endif //IRIS_CONSTANTS_H
