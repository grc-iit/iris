/*******************************************************************************
* File HyperdexClient.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
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
  int logRequest(int64_t operationId,const char * OPERATION_TYPE,Key &key,const hyperdex_client_attribute **attributes, size_t *attributes_sz);
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
