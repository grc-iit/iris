//
// Created by anthony on 12/10/16.
//

#include "S3MetadataManager.h"

int S3MetadataManager::getFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()) return FH_DOES_NOT_EXIST;
  virtualFile.setFh(iterator->second);
  return OPERATION_SUCCESSFUL;
}

int S3MetadataManager::updateFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()){
    filenameToFile.insert(std::make_pair(virtualFile.getFilename(),
                                         virtualFile.getFh()));
  }
  else{
    filenameToFile[iterator->first] = virtualFile.getFh();
  }
  return OPERATION_SUCCESSFUL;
}

int S3MetadataManager::deleteFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()) return FH_DOES_NOT_EXIST;
  filenameToFile.erase(iterator->first);
  return OPERATION_SUCCESSFUL;
}