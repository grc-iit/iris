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
#include <iostream>
#include <chrono>
#include "../return_codes.h"
#include "ObjectStorePrefetcher.h"
#include "../mapper/POSIXMapper.h"
#include "tools/Timer.h"

/******************************************************************************
*Constructor
******************************************************************************/
ObjectStorePrefetcher::ObjectStorePrefetcher() {
  objectStoreFactory=ObjectStoreFactory::getInstance();
  cacheManager=CacheManager::getInstance();
  mapperFactory=MapperFactory::getInstance();
}
/******************************************************************************
*Destructor
******************************************************************************/
ObjectStorePrefetcher::~ObjectStorePrefetcher() {}
/******************************************************************************
*Interface
******************************************************************************/
int ObjectStorePrefetcher::fetch(const char *fileName, long int fileOffset,
                                 size_t operationSize, long int fileSize) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
#ifdef DEBUG
  std::cout << "####################  PREFETCHER ################" << std::endl;
#endif/*DEBUG*/
  auto posixMapper = std::static_pointer_cast<POSIXMapper>
      (mapperFactory->getMapper(POSIX_MAPPER));
  int status = engine(fileName, fileOffset, operationSize, fileSize,
                      PREFETCH_MODE);
  if(status == OPERATION_SUCCESSFUL){
    auto keys = posixMapper->generateKeys(fileName, fileOffset, operationSize);
    fetchKeys(keys);
  }
  else return FETCH_FAILED;

#ifdef TIMER
timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int ObjectStorePrefetcher::fetchKeys(std::vector<Key> keys) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  for (auto key:keys) fetchKey(key);
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int ObjectStorePrefetcher::fetchKey(Key key) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  auto objectStoreClient = std::static_pointer_cast<HyperdexClient>
      (objectStoreFactory->getObjectStore(HYPERDEX_CLIENT));
  if(cacheManager->isCached(key) != OPERATION_SUCCESSFUL){
    if(objectStoreClient->get(key) == OPERATION_SUCCESSFUL)
      cacheManager->addToCache(key);
  }
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}
int ObjectStorePrefetcher::engine(const char *fileName, long int &fileOffset,
                                  size_t &operationSize, long int fileSize,
                                  int prefetchingMode) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  switch(prefetchingMode){
    case SEQUENTIAL:
      if(fileOffset+operationSize <= fileSize-operationSize)
        fileOffset += operationSize;
      else return PREFETCH_ENGINE_FAILED;
      break;
    case STRIDED:

      break;
    case RANDOM:
      fileOffset = operationSize*rand()%(fileSize/operationSize+1);
      if(fileOffset >= fileSize) return PREFETCH_ENGINE_FAILED;
      break;
    case USER_DEFINED:

      break;
    default:
      fprintf(stderr, "Prefetch Mode is no valid!\n");
      return PREFETCH_ENGINE_FAILED;
  }
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}







