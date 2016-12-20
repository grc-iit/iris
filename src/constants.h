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

#include "return_codes.h"
/******************************************************************************
*Prefetcher
******************************************************************************/
#define FILESYSTEM_PREFETCHER "FILESYSTEM_PREFETCHER"
#define OBJECTSTORE_PREFETCHER "OBJECTSTORE_PREFETCHER"
/******************************************************************************
*Metadata Manager
******************************************************************************/
#define IRIS_METADATA_MANAGER "IRIS_METADATA_MANAGER"
#define POSIX_METADATA_MANAGER "POSIX_METADATA_MANAGER"
#define MPIIO_METADATA_MANAGER "MPIIO_METADATA_MANAGER"
#define HDF5_METADATA_MANAGER "HDF5_METADATA_MANAGER"
#define PNETCDF_METADATA_MANAGER "PNETCDF_METADATA_MANAGER"
#define S3_METADATA_MANAGER "S3_METADATA_MANAGER"
/******************************************************************************
*Mapper
******************************************************************************/
#define POSIX_MAPPER "POSIX_MAPPER"
#define MPIIO_MAPPER "MPIIO_MAPPER"
#define HDF5_MAPPER "HDF5_MAPPER"
#define PNETCDF_MAPPER "PNETCDF_MAPPER"
#define S3_MAPPER "S3_MAPPER"
/******************************************************************************
*Key structure
******************************************************************************/
struct Key{
    char * name;
    size_t offset;
    size_t size;
    void* data;
};
/******************************************************************************
*Iris library parameters
******************************************************************************/
#define MAX_FILENAME_LENGTH 256
#define FILE_BUFFER_CAPACITY 1
#define POSIX_MODE "STRICT" // "RELAXED"
#define MAX_KEY_LENGTH 32
#define MAX_OBJ_SIZE 20



#endif //IRIS_CONSTANTS_H