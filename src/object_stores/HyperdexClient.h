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
#include "AbstractObjectStore.h"
#include "../constants.h"
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
  int getRange(std::vector<Key> keys);
  /*TODO:
  int put_range(std::vector<Key> keys);*/
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~HyperdexClient();
};

#endif //IRIS_HYPERDEXCLIENT_H
