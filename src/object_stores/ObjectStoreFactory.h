//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_OBJECTSTOREFACTORY_H
#define IRIS_OBJECTSTOREFACTORY_H


#include <memory>
#include "AbstractObjectStore.h"

class ObjectStoreFactory {
private:
  static std::shared_ptr<ObjectStoreFactory> instance;
  ObjectStoreFactory();

public:
  static std::shared_ptr<ObjectStoreFactory> getInstance();
  std::shared_ptr<AbstractObjectStore> getObjectStore(const
                                                      char* name);
  virtual ~ObjectStoreFactory();
};


#endif //IRIS_OBJECTSTOREFACTORY_H
