//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_METADATAMANAGERFACTORY_H
#define IRIS_METADATAMANAGERFACTORY_H

#include <bits/unique_ptr.h>
#include "AbstractMetadataManager.h"

class MetadataManagerFactory {
private:
  static std::unique_ptr<MetadataManagerFactory> instance;
  MetadataManagerFactory();
  virtual ~MetadataManagerFactory();

public:
  static std::unique_ptr<MetadataManagerFactory> getInstance();
  std::unique_ptr<AbstractMetadataManager> getMetadataManager(const char* name);
};


#endif //IRIS_METADATAMANAGERFACTORY_H
