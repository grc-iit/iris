//
// Created by anthony on 12/10/16.
//

#include "PVFS2Client.h"
#include "../metadata_manager/S3MetadataManager.h"
#include <sys/mman.h>

int PVFS2Client::fopen(Container &container) {
  auto s3MetadataManager = std::static_pointer_cast<S3MetadataManager>
      (metadataManagerFactory->getMetadataManager(S3_METADATA_MANAGER));
  int status=s3MetadataManager->getFileHandler(container);
  if(status!=OPERATION_SUCCESSFUL){
    FILE *fh;
    std::string filePath = WORKING_DIRECTORY + container.getFilename();
    fh=std::fopen(filePath.c_str(), "w+");
    container.setFh(fh);
    s3MetadataManager->updateFileHandler(container);
  }
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fclose(Container &container) {
  if(container.isFilled()){
    auto s3MetadataManager = std::static_pointer_cast<S3MetadataManager>
        (metadataManagerFactory->getMetadataManager(S3_METADATA_MANAGER));
    int status=s3MetadataManager->getFileHandler(container);
    if(status==OPERATION_SUCCESSFUL){
      std::fclose(container.getFh());
      s3MetadataManager->deleteFileHandler(container);
    }
  }
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fread(Container &container) {
  std::fread(container.getData(),sizeof(char),
               container.getSize()-container.getOffset(),container.getFh());


  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fwrite(Container &container) {
  std::fwrite(container.getData(),sizeof(char),
             container.getSize()-container.getOffset(),container.getFh());
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fseek(Container &container) {
  std::fseek(container.getFh(),container.getOffset(),SEEK_SET);
  return OPERATION_SUCCESSFUL;
}
