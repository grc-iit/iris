//
// Created by anthony on 12/10/16.
//

#include "S3Mapper.h"
#include "../constants.h"
/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<S3Mapper> S3Mapper::instance = nullptr;

VirtualFile S3Mapper::generateFiles(std::string keyName,std::size_t
objectSize) {
  //first we get the filename from hash function
  std::size_t hash=hashKey(keyName, objectSize);
  std::string filename = "tmpfile_"
                          + std::to_string(hash)
                          + ".dat";
  VirtualFile virtualFile;
  auto iterator = fileNameToFile.find(filename);
  if(iterator ==  fileNameToFile.end()){
    //if file is new create a new Virtual file and set the key parameters
    virtualFile=VirtualFile();
    virtualFile.setFilename(filename);
    virtualFile.setOffset(0);
    virtualFile.setSize(objectSize);
    virtualFile.getKeyList().insert(keyName);
  }
  else{
    // if file name exist then update the Virtual file with new parameters
    virtualFile=iterator->second;
    virtualFile.setOffset(virtualFile.getSize());
    virtualFile.setSize(virtualFile.getSize()+objectSize);
    virtualFile.getKeyList().insert(keyName);
    fileNameToFile.erase(filename);
  }
  if(currentFileSize+objectSize<=MAX_VF_SIZE){
    virtualFile.setFilled(true);
  }
  currentFileSize=virtualFile.getSize();
  currentHash=hash;
  fileNameToFile.insert(std::make_pair(filename, virtualFile));
  return virtualFile;
}

size_t S3Mapper::hashKey(std::string keyName,std::size_t
objectSize) {
  if(currentFileSize+objectSize<=MAX_VF_SIZE){
    return currentHash;
  }
  size_t hash = SEED;
  for(auto s: keyName)
  {
    hash = hash * 101  +  s++;
  }
  return hash;
}


