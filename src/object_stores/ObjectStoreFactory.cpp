//
// Created by anthony on 12/10/16.
//

#include "ObjectStoreFactory.h"
#include "HyperdexClient.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<ObjectStoreFactory> ObjectStoreFactory::instance = nullptr;

ObjectStoreFactory::ObjectStoreFactory() {}

ObjectStoreFactory::~ObjectStoreFactory() {}

std::shared_ptr<ObjectStoreFactory> ObjectStoreFactory::getInstance() {
  if (instance == nullptr) {
    instance = std::shared_ptr<ObjectStoreFactory>(new ObjectStoreFactory());
  }
  return instance;
}

std::shared_ptr<AbstractObjectStore> ObjectStoreFactory::getObjectStore(std::string name) {
  std::shared_ptr<AbstractObjectStore> objectStoreClient;
  if (name == HYPERDEX_CLIENT) {
    objectStoreClient =
        std::static_pointer_cast<HyperdexClient>(HyperdexClient::getInstance());
  }
  return objectStoreClient;
}


