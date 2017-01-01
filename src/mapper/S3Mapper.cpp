//
// Created by anthony on 12/10/16.
//

#include "S3Mapper.h"
#include "../constants.h"

/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<S3Mapper> S3Mapper::instance = nullptr;

Container S3Mapper::mapObject(std::string objectName, std::size_t objectSize) {
  //first we get the filename from hash function
  std::size_t hashValue = hashKey(objectName, objectSize);
  std::string filename = "container_"
                         + std::to_string(hashValue)
                         + ".dat";
  Container container;
  auto iterator = containerList.find(filename);
  if(iterator == containerList.end()){
    container = Container();
    container.setFilename(filename);
    containerList.insert({filename, container});
  }
  else container = iterator->second;
  return container;
}

std::size_t S3Mapper::hashKey(std::string objectName, std::size_t objectSize) {
  auto keyIterator = keyToHash.find(objectName);
  std::size_t hash;
  if (keyIterator != keyToHash.end()) {
    hash = keyIterator->second;
  }
  else {
    hash = CityHash64WithSeed(objectName.c_str(), strlen(objectName), SEED);
    keyToHash.insert(std::make_pair(objectName,hash));
  }
  return hash;
}



