//
// Created by anthony on 12/10/16.
//

#include "ObjectStoreFactory.h"
#include "HyperdexClient.h"

std::unique_ptr<ObjectStoreFactory> ObjectStoreFactory::getInstance() {
    if (instance == nullptr) {
        instance = new ObjectStoreFactory();
    }
    return instance;
}

std::unique_ptr<AbstractObjectStore> ObjectStoreFactory::getObjectStore(std::string name) {
    std::unique_ptr<AbstractObjectStore> objectStoreClient;
    if (name == HYPERDEX_CLIENT) {
        objectStoreClient = HyperdexClient::getInstance();
    }
    return std::unique_ptr<AbstractObjectStore>();
}
