//
// Created by anthony on 12/10/16.
//
#include <cstring>
#include <memory>
#include "FileSystemFactory.h"
#include "../constants.h"
#include "PVFS2Client.h"

/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<FileSystemFactory> FileSystemFactory::instance = nullptr;

std::shared_ptr<AbstractFileSystem>
FileSystemFactory::getFileSystem(const char *name) {
  std::shared_ptr<AbstractFileSystem> fileSystemClient;
  if (strcmp(name,PVFS2_CLIENT)==0) {
    fileSystemClient = std::shared_ptr<PVFS2Client>(new PVFS2Client());
  }
  return fileSystemClient;
}
