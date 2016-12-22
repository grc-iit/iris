//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_METADATAMANAGERFACTORY_H
#define IRIS_METADATAMANAGERFACTORY_H

#include <memory>
#include "IrisMetadataManager.h"

class MetadataManagerFactory {
private:
  static std::shared_ptr<MetadataManagerFactory> instance;
  MetadataManagerFactory();
public:
  static std::shared_ptr<MetadataManagerFactory> getInstance();
  std::shared_ptr<IrisMetadataManager> getMetadataManager(const char* name);
  virtual ~MetadataManagerFactory();
};


#endif //IRIS_METADATAMANAGERFACTORY_H
