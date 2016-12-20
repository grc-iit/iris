//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_OBJECTSTOREFACTORY_H
#define IRIS_OBJECTSTOREFACTORY_H


#include <memory>
#include "AbstractObjectStore.h"

class ObjectStoreFactory {
private:
    static std::unique_ptr<ObjectStoreFactory> instance;

    ObjectStoreFactory() {

    }

public:
    static std::unique_ptr<ObjectStoreFactory> getInstance();
    std::unique_ptr<AbstractObjectStore> getObjectStore(std::string name);
};


#endif //IRIS_OBJECTSTOREFACTORY_H
