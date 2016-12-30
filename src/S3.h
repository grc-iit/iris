/*******************************************************************************
* File S3.h
*
* Goal: This is the POSIX interface
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_S3_H
#define IRIS_S3_H
/******************************************************************************
*include files
******************************************************************************/
#include "API.h"

namespace iris {
/******************************************************************************
*Interface operations
******************************************************************************/
  int64_t hyperdex_client_get(struct hyperdex_client* client,
                              const char* space,
                              const char* key,
                              size_t key_sz,
                              enum hyperdex_client_returncode* status,
                              const struct hyperdex_client_attribute** attrs,
                              size_t* attrs_sz);

  int64_t hyperdex_client_put(struct hyperdex_client* client,
                              const char* space,
                              const char* key,
                              size_t key_sz,
                              const struct hyperdex_client_attribute* attrs,
                              size_t attrs_sz,
                              enum hyperdex_client_returncode* status);

  int64_t hyperdex_client_del(struct hyperdex_client* client,
                              const char* space,
                              const char* key,
                              size_t key_sz,
                              enum hyperdex_client_returncode* status);

}
#endif //IRIS_S3_H

















