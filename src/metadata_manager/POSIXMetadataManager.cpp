/******************************************************************************
*include files
******************************************************************************/
#include "POSIXMetadataManager.h"
#include "../constants.h"
/******************************************************************************
*Constructor
******************************************************************************/
POSIXMetadataManager::POSIXMetadataManager(){
  created_files=std::unordered_map<const char *,Stat>();
  fh2filename=std::unordered_map<FILE *,const char *>();
  pointer=std::unordered_map<FILE *,long int>();
}
/******************************************************************************
*Destructor
******************************************************************************/
POSIXMetadataManager::~POSIXMetadataManager() {
  //TODO: serialize structures with flatbuffers and send down to ObjectStore
}
/******************************************************************************
*Interface
******************************************************************************/
bool POSIXMetadataManager::checkIfFileExists(const char * filename) {
  /*Check if the filename is longer than allowed (<256)*/
  if(std::strlen(filename) > MAX_FILENAME_LENGTH){
    fprintf(stderr, "ERROR! File name too long!\n fn: checkIfFileExists");
    exit(-1);
  }
  /* Check if the filename exists in the map of the created files*/
  std::unordered_map<const char *, Stat>::const_iterator
      fileIterator = created_files.find(filename);
  return !(fileIterator == created_files.end());
}

bool POSIXMetadataManager::checkIfFileIsOpen(const char *filename) {
  /*Check if the filename is longer than allowed (<256)*/
  if(std::strlen(filename) > MAX_FILENAME_LENGTH){
    fprintf(stderr, "ERROR! File name too long!\n fn: checkIfFileIsOpen");
    exit(-1);
  }
  if(checkIfFileExists(filename)) {
    /* Check if the file has been previously been opened*/
    std::unordered_map<const char *, Stat>::const_iterator
        fileIterator = created_files.find(filename);
    if (fileIterator == created_files.end()) return false;
    return created_files[filename].opened;
  }
  else{
#ifdef DEBUG
    fprintf(stderr, "Check if file is opened failed because file does not
    exist! Please check the file name\n  fn: checkIfFileIsOpen");
#endif /* DEBUG*/
    return false;
  }
}

const char *POSIXMetadataManager::getFilename(FILE *fh) {
  if(fh == nullptr) return nullptr;
  std::unordered_map<FILE *, const char *>::const_iterator iterator =
      fh2filename.find(fh);
  if(iterator == fh2filename.end()) return nullptr;
  else return iterator->second; //holds the filename
}

int POSIXMetadataManager::createMetadata(FILE * fh, const char * filename,
                                         const char* mode) {
  //Error checks
  if(fh == nullptr || std::strlen(filename) > MAX_FILENAME_LENGTH)
    return METADATA_CREATION_FAILED;
  Stat file_metadata;
  if(strcmp(POSIX_MODE,"STRICT")==0)
    file_metadata = {true, mode, getuid(), getgid(), 0, time(NULL), time(NULL),
                     time(NULL)};
  else file_metadata = {true, mode, 0, 0, 0, 0, 0, 0};
  created_files.insert(std::make_pair(filename,file_metadata));
  fh2filename.insert(std::make_pair(fh, filename));
  pointer.insert(std::make_pair(fh,0));
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnOpen(FILE * fh, const char * filename,
                                               const char* mode) {
  //Error checks
  if(fh == nullptr || std::strlen(filename) > MAX_FILENAME_LENGTH)
    return METADATA_UPDATE_FAILED__OPEN;
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
  //Error checks
  if(fh == nullptr || std::strlen(filename) > MAX_FILENAME_LENGTH)
    return METADATA_UPDATE_FAILED__CLOSE;
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
  //Error checks
  if(fh == nullptr || operationSize == 0) return METADATA_UPDATE_FAILED__READ;
  const char * filename = getFilename(fh);
  if(filename == nullptr) return FILENAME_DOES_NOT_EXIST;
  if(strcmp(POSIX_MODE,"STRICT")==0) created_files[filename].atime = time(NULL);
  updateFpPosition(fh, operationSize, SEEK_CUR);
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateMetadataOnWrite(FILE *fh,
                                                std::size_t operationSize) {
  if(fh == nullptr || operationSize == 0) return METADATA_UPDATE_FAILED__WRITE;
  const char * filename = getFilename(fh);
  if(filename == nullptr) return FILENAME_DOES_NOT_EXIST;
  if(strcmp(POSIX_MODE,"STRICT")==0){
    created_files[filename].atime = time(NULL);
    created_files[filename].mtime = time(NULL);
  }
  long int fileOffset = getFpPosition(fh);
  if(fileOffset < 0) return FP_DOES_NOT_EXIST;
  created_files[filename].st_size =
      fileOffset + operationSize > created_files[filename].st_size
      ? fileOffset + operationSize : created_files[filename].st_size;
  updateFpPosition(fh, operationSize, SEEK_CUR);
  return OPERATION_SUCCESSUL;
}

int POSIXMetadataManager::updateFpPosition(FILE *fh, long int offset,
                                           int origin) {
  if(fh == nullptr) return UPDATE_FILE_POINTER_FAILED;
  std::unordered_map<FILE *, long int>::const_iterator index =
      pointer.find(fh);
  if(index == pointer.end()) return UPDATE_FILE_POINTER_FAILED;

  const char * filename = getFilename(fh);
  if(filename == nullptr) return FILENAME_DOES_NOT_EXIST;
  switch(origin){
    case SEEK_SET:
      pointer[index->first] = 0+offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename))
        return UPDATE_FILE_POINTER_FAILED;
      break;
    case SEEK_CUR:
      pointer[index->first] += offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename))
        return UPDATE_FILE_POINTER_FAILED;
      break;
    case SEEK_END:
      pointer[index->first] = getFilesize(filename) + offset;
      if(pointer[index->first] <0 || pointer[index->first] > getFilesize(filename))
        return UPDATE_FILE_POINTER_FAILED;
      break;
    default:
      fprintf(stderr, "Seek origin fault!\n");
      return UPDATE_FILE_POINTER_FAILED;
  }
  return OPERATION_SUCCESSUL;
}

long int POSIXMetadataManager::getFpPosition(FILE *fh) {
  if(fh == nullptr) return -1;
  std::unordered_map<FILE *, long int>::const_iterator index =
      pointer.find(fh);
  if(index == pointer.end()) return -1;
  else return index->second; //holds the offset
}

/******************************************************************************
*Functions
******************************************************************************/
long int POSIXMetadataManager::getFilesize(const char *filename) {
  if(!checkIfFileExists(filename) || std::strlen(filename) > MAX_FILENAME_LENGTH)
    return -1;
  std::unordered_map<const char *, Stat>::const_iterator fileIterator
      = created_files.find(filename);
  if(fileIterator == created_files.end()) return -1;
  return fileIterator->second.st_size;
}







