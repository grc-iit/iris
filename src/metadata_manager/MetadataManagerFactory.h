//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_METADATAMANAGERFACTORY_H
#define IRIS_METADATAMANAGERFACTORY_H

#include "AbstractMetadataManager.h"

class MetadataManagerFactory {
private:
  static MetadataManagerFactory* instance;
  MetadataManagerFactory();
  virtual ~MetadataManagerFactory();

public:
  static MetadataManagerFactory* getInstance();
  AbstractMetadataManager* getMetadataManager(const char* name);
};


#endif //IRIS_METADATAMANAGERFACTORY_H
