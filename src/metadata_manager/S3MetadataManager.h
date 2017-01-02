//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_S3METADATAMANAGER_H
#define IRIS_S3METADATAMANAGER_H

#include <unordered_map>
#include "IrisMetadataManager.h"
#include "../constants.h"

class S3MetadataManager: public IrisMetadataManager {
private:
  std::unordered_map<std::string, FILE *> filenameToFile;
public:
  S3MetadataManager(){
    filenameToFile = std::unordered_map<std::string, FILE *>();
  }
  int getFileHandler(VirtualFile & virtualFile);
  int updateFileHandler(VirtualFile & virtualFile);
  int deleteFileHandler(VirtualFile &virtualFile);
};


#endif //IRIS_S3METADATAMANAGER_H
