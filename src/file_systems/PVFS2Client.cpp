/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
//
// Created by anthony on 12/10/16.
//

#include "PVFS2Client.h"
#include "../metadata_manager/S3MetadataManager.h"
#include <sys/mman.h>

int PVFS2Client::fopen(VirtualFile &virtualFile) {

  auto s3MetadataManager = std::static_pointer_cast<S3MetadataManager>
      (metadataManagerFactory->getMetadataManager(S3_METADATA_MANAGER));
  int status=s3MetadataManager->getFileHandler(virtualFile);
  if(status!=OPERATION_SUCCESSFUL){
    FILE *fh;
    std::string filePath = TEMP_LOCATION + virtualFile.getFilename();
    fh=std::fopen(filePath.c_str(), "w+");
    void* mmappedData = mmap(NULL,
                             MAX_VF_SIZE,
                             PROT_READ || PROT_WRITE,
                             MAP_SHARED | MAP_POPULATE,
                             fileno(fh), 0);
    virtualFile.setMmappedData(mmappedData);
    virtualFile.setFh(fh);
    s3MetadataManager->updateFileHandler(virtualFile);
  }
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fclose(VirtualFile &virtualFile) {
  if(virtualFile.isFilled()){
    auto s3MetadataManager = std::static_pointer_cast<S3MetadataManager>
        (metadataManagerFactory->getMetadataManager(S3_METADATA_MANAGER));
    int status=s3MetadataManager->getFileHandler(virtualFile);
    if(status==OPERATION_SUCCESSFUL){
      if (munmap(virtualFile.getMmappedData(), virtualFile.getSize()) == -1) {
        perror("Error un-mmapping the file");
      }
      std::fclose(virtualFile.getFh());
      s3MetadataManager->deleteFileHandler(virtualFile);
    }
  }
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fread(VirtualFile &virtualFile) {
  std::fread(virtualFile.getData(),sizeof(char),
               virtualFile.getSize()-virtualFile.getOffset(),virtualFile.getFh());


  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fwrite(VirtualFile &virtualFile) {
  std::fwrite(virtualFile.getData(),sizeof(char),
             virtualFile.getSize()-virtualFile.getOffset(),virtualFile.getFh());
  return OPERATION_SUCCESSFUL;
}

int PVFS2Client::fseek(VirtualFile &virtualFile) {
  std::fseek(virtualFile.getFh(),virtualFile.getOffset(),SEEK_SET);
  return OPERATION_SUCCESSFUL;
}
