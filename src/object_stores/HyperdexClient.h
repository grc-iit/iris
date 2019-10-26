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
* File HyperdexClient.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_HYPERDEXCLIENT_H
#define IRIS_HYPERDEXCLIENT_H
/******************************************************************************
*include files
******************************************************************************/
#include <memory>
#include <vector>
#include <hyperdex/client.h>
#include "AbstractObjectStore.h"
#include "../constants.h"
#include "../utils/CacheManager.h"
#include "../utils/PrefetcherFactory.h"

/******************************************************************************
*Class
******************************************************************************/
class HyperdexClient : public AbstractObjectStore {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  static std::shared_ptr<HyperdexClient> instance;
  struct hyperdex_client* hyperdexClient;
  std::shared_ptr<CacheManager> cacheManager;
  std::shared_ptr<PrefetcherFactory> prefetcherFactory;
  struct OperationData{
      int operationType;
      int completionStatus;
      Key* key;
      const hyperdex_client_attribute **attributes;
      size_t *attributes_sz;
  };
  std::unordered_map<int64_t,OperationData> operationToKeyMap;
  int getKey(int64_t operationId,Key &key);
  int logRequest(int64_t operationId,
                 const char * OPERATION_TYPE,
                 Key &key,
                 const hyperdex_client_attribute **attributes,
                 size_t *attributes_sz);
/******************************************************************************
*Constructor
******************************************************************************/
  HyperdexClient();
/******************************************************************************
*Init function
******************************************************************************/
  int init();
public:
/******************************************************************************
*Getters and setters
******************************************************************************/
  inline static std::shared_ptr<HyperdexClient> getInstance(){
    return instance == nullptr ? instance = std::shared_ptr<HyperdexClient>
        (new HyperdexClient())
                               : instance;
  }
/******************************************************************************
*Interface
******************************************************************************/
  int get(Key &key) override;
  int put(Key &key) override;
  int remove(Key &key) override;
/* Hyperdex specific calls*/
  int getRange(std::vector<Key> &keys);
  int putRange(std::vector<Key> &keys);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~HyperdexClient();

    int getKeyFromMap(int64_t operationId, Key &key);
};

#endif //IRIS_HYPERDEXCLIENT_H
