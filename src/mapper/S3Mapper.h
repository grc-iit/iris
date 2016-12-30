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

class S3Mapper: public AbstractMapper {
private:
  static std::shared_ptr<S3Mapper> instance;
  std::unordered_map<std::string, VirtualFile> fileNameToFile;
  size_t hashKey(std::string keyName,std::size_t objectSize);
  size_t currentFileSize;
  std::size_t currentHash;
  S3Mapper() {
    fileNameToFile = std::unordered_map<std::string, VirtualFile>();
    currentFileSize=0;
    currentHash=-1;
  }
public:
  VirtualFile generateFiles(std::string keyName,std::size_t
  objectSize);

  static std::shared_ptr<S3Mapper> getInstance() {
    return instance == nullptr ? instance =
                                     std::shared_ptr<S3Mapper>(new S3Mapper())
                               : instance;
  }
};

#endif //IRIS_S3MAPPER_H
