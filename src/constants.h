/*******************************************************************************
* File constants.h
*
* Goal: Define various library constants and system parameters
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_CONSTANTS_H
#define IRIS_CONSTANTS_H
/******************************************************************************
*include files
******************************************************************************/
#include <cstring>
#include <sys/types.h>
#include <string>
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
static const size_t MAX_OBJ_SIZE = (20*1024);
static const u_int64_t CACHE_CAPACITY = 1073741824;
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
*Key structure
******************************************************************************/
struct Key{
    const char * name;
    std::size_t offset;
    std::size_t size;
    void* data;
};

#endif //IRIS_CONSTANTS_H
