//
// Created by anthony on 12/10/16.
//

#include "POSIXMetadataManager.h"
#include "../constants.h"

bool POSIXMetadataManager::checkIfFileExists(const char * filename) {
  std::unordered_map<const char *, Stat>::const_iterator
      fileIterator = created_files.find(filename);
  return !(fileIterator == created_files.end());
}

bool POSIXMetadataManager::checkIfFileIsOpen(const char *filename) {
  std::unordered_map<const char *, Stat>::const_iterator
      fileIterator = created_files.find(filename);
  if(fileIterator==created_files.end()) return false;
  return created_files[filename].opened;
}

const char *POSIXMetadataManager::getFilename(FILE *fh) {
  const char * filename;
  std::unordered_map<FILE *, const char *>::const_iterator iterator =
      fh2filename.find(fh);
  if(iterator == fh2filename.end()) return nullptr;
  else filename =  iterator->second;
  return filename;
}

int POSIXMetadataManager::createMetadata(FILE * fh, const char * filename, const char* mode) {
  //TODO: error checking
  Stat file_metadata;
  if(strcmp(POSIX_MODE,"STRICT")==0) file_metadata = {true, mode, getuid(), getgid(), 0,
                          time(NULL), time(NULL), time(NULL)};
  else file_metadata = {true, mode, 0, 0, 0, 0, 0, 0};

  created_files.insert(std::make_pair(filename,file_metadata));
  fh2filename.insert(std::make_pair(fh, filename));
  pointer.insert(std::make_pair(fh,0));
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnOpen(FILE * fh, const char * filename, const char* mode) {
  //TODO: error checking
  if(strcmp(POSIX_MODE,"STRICT")==0)
  created_files[filename] = {true, mode, created_files[filename].st_uid, created_files[filename].st_gid,
                             created_files[filename].st_size, time(NULL),
                             created_files[filename].mtime,
                             created_files[filename].ctime};
  else created_files[filename] = {true, mode, 0, 0,
                                  created_files[filename].st_size, 0, 0, 0};
  fh2filename.insert(std::make_pair(fh, filename));
  pointer.insert(std::make_pair(fh,0));
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnClose(FILE * fh, const char * filename) {
  //TODO: error checking
  if(strcmp(POSIX_MODE,"STRICT")==0){
    created_files[filename].opened = false;
    created_files[filename].atime = time(NULL);
  }
  else created_files[filename].opened = false;

  fh2filename.erase(fh);
  pointer.erase(fh);
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnRead(FILE *fh, std::size_t operationSize) {
  //TODO: error checking
  const char * filename = getFilename(fh);
  if(strcmp(POSIX_MODE,"STRICT")==0) created_files[filename].atime = time(NULL);
  updateFpPosition(fh, operationSize, SEEK_CUR);
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnWrite(FILE *fh,
                                                std::size_t operationSize) {
  //TODO: error checking
  const char * filename = getFilename(fh);
  if(strcmp(POSIX_MODE,"STRICT")==0){
    created_files[filename].atime = time(NULL);
    created_files[filename].mtime = time(NULL);
  }
  std::size_t fileOffset = getFpPosition(fh);
  created_files[filename].st_size = fileOffset + operationSize > created_files[filename].st_size ? fileOffset + operationSize : created_files[filename].st_size;
  updateFpPosition(fh, operationSize, SEEK_CUR);
  return OPERATION_SUCCESSUL;
}

long int POSIXMetadataManager::getFilesize(const char *filename) {
  std::unordered_map<const char *, Stat>::const_iterator fileIterator
        = created_files.find(filename);
  if(fileIterator == created_files.end()) return -1;
  return fileIterator->second.st_size;
}

int POSIXMetadataManager::updateFpPosition(FILE *fh, long int offset, int origin) {
  std::unordered_map<FILE *, long int>::const_iterator index =
      pointer.find(fh);
  if(index == pointer.end()) return UPDATE_FILE_POINTER_FAILED;

  const char * filename = getFilename(fh);
  switch(origin){
    case SEEK_SET:
      pointer[index->first] = 0+offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename)) return UPDATE_FILE_POINTER_FAILED;
      break;
    case SEEK_CUR:
      pointer[index->first] += offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename)) return UPDATE_FILE_POINTER_FAILED;
      break;
    case SEEK_END:
      pointer[index->first] = getFilesize(filename) + offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename)) return UPDATE_FILE_POINTER_FAILED;
      break;
    default:
      fprintf(stderr, "Seek origin fault!\n");
      return UPDATE_FILE_POINTER_FAILED;
  }
  return OPERATION_SUCCESSUL;
}

size_t POSIXMetadataManager::getFpPosition(FILE *fh) {
  std::unordered_map<FILE *, long int>::const_iterator index =
      pointer.find(fh);
  if(index == pointer.end()) return FP_NOT_EXIST;
  else return (size_t)index->second;
}






