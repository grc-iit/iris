//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_S3MAPPER_H
#define IRIS_S3MAPPER_H

#include <vector>
#include <unordered_map>
#include <memory>
#include "AbstractMapper.h"
#include "../constants.h"
#include "../metadata_manager/MetadataManagerFactory.h"

class S3Mapper: public AbstractMapper {
private:
  static std::shared_ptr<S3Mapper> instance;
  std::unordered_map<std::string, Container> containerList;
  std::unordered_map<std::string, std::size_t> keyToHash;
  S3Mapper() {
    keyToHash = std::unordered_map<std::string, std::size_t>();
    containerList = std::unordered_map<std::string, Container>();
  }
public:
  static std::shared_ptr<S3Mapper> getInstance() {
    return instance == nullptr ? instance =
                                     std::shared_ptr<S3Mapper>(new S3Mapper())
                               : instance;
  }
  Container mapObject(std::string objectName, std::size_t objectSize);
  std::size_t hashKey(std::string objectName, std::size_t objectSize);

  std::unordered_map<std::string, Container> getContainerList() {
    return containerList;
  }
};

#endif //IRIS_S3MAPPER_H
