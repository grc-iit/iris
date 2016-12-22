//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_HYPERDEXCLIENT_H
#define IRIS_HYPERDEXCLIENT_H


#include <memory>
#include <vector>
#include "AbstractObjectStore.h"
#include "../constants.h"

class HyperdexClient : public AbstractObjectStore {
private:
  static std::unique_ptr<HyperdexClient> instance;
  HyperdexClient();
  int init();
  struct hyperdex_client* hyperdexClient;
public:
  static std::unique_ptr<HyperdexClient> getInstance();

  int get(Key &key) override;

  int put(Key &key) override;

  int remove(Key &key) override;

  virtual ~HyperdexClient();


};


#endif //IRIS_HYPERDEXCLIENT_H
