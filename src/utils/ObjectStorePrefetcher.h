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
* File ObjectStorePrefetcher.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_OBJECTSTOREPREFETCHER_H
#define IRIS_OBJECTSTOREPREFETCHER_H
/******************************************************************************
*include files
******************************************************************************/
#include "AbstractPrefetcher.h"
#include "../constants.h"
#include "../object_stores/HyperdexClient.h"
#include "../object_stores/ObjectStoreFactory.h"
#include "../mapper/MapperFactory.h"
#include "CacheManager.h"
#include <vector>
/******************************************************************************
*Class
******************************************************************************/
class ObjectStorePrefetcher: public AbstractPrefetcher{
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  std::shared_ptr<ObjectStoreFactory> objectStoreFactory;
  std::shared_ptr<CacheManager> cacheManager;
  std::shared_ptr<MapperFactory> mapperFactory;
/******************************************************************************
*Functions
******************************************************************************/
  int engine(const char * fileName, long int &fileOffset, size_t &operationSize,
             long int fileSize, int prefetchingMode);
public:
/******************************************************************************
*Constructor
******************************************************************************/
  ObjectStorePrefetcher();
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~ObjectStorePrefetcher();
/******************************************************************************
*Interface
******************************************************************************/
  int fetch(const char *fileName, long int fileOffset, size_t operationSize,
            long int fileSize);
  int fetchKey(Key key);
  int fetchKeys(std::vector<Key> keys);
};


#endif //IRIS_OBJECTSTOREPREFETCHER_H
