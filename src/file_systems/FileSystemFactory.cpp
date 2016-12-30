//
// Created by anthony on 12/10/16.
//
#include <cstring>
#include "FileSystemFactory.h"
#include "PVFS2Client.h"

std::shared_ptr<AbstractFileSystem>
FileSystemFactory::getFileSystem(const char *name) {
  std::shared_ptr<AbstractFileSystem> fileSystemClient;
  if (strcmp(name,PVFS2_CLIENT)==0) {
    fileSystemClient =
        std::static_pointer_cast<PVFS2Client>(new PVFS2Client());
  }
  return fileSystemClient;
}
