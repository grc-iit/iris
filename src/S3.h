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
* File S3.h
*
* Goal: This is the POSIX interface
*
* Created: December 10th, 2016  - Anthony Kougkas
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

















