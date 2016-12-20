//
// Created by anthony on 12/10/16.
//

#include "HyperdexClient.h"

HyperdexClient::HyperdexClient() {}

HyperdexClient::~HyperdexClient() {}


std::unique_ptr<HyperdexClient> HyperdexClient::getInstance() {
  if (instance == nullptr) {
    instance = new HyperdexClient();
  }
  return instance;
}

int HyperdexClient::get(Key key, void *&data) {
  return 0;
}

int HyperdexClient::put(Key key, void *data) {
  return 0;
}

int HyperdexClient::remove(Key key) {
  return 0;
}

int HyperdexClient::gets(std::vector<Key> key, std::vector<void *> &data) {
  return 0;
}

