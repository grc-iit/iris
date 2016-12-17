//
// Created by anthony on 12/10/16.
//

#include "POSIXMetadataManager.h"

bool POSIXMetadataManager::checkIfFileCreated(const char * filename) {
    std::unordered_map<const char *, Stat>::const_iterator
            fileIterator = created_files.find(filename);
    return !(fileIterator == created_files.end());
}

int POSIXMetadataManager::createMetadata(FILE *fh) {
    opened_fh.insert(std::make_pair(fh, ++fildes));
    if(consisteny==STRONG) {

        apiInstance.getMetadatManager(POSIX)->updateStat()
        Stat file_metadata = {true, mode, getuid(), getgid(), 0,
                              time(NULL), time(NULL), time(NULL)};
    }
    created_files.insert(std::make_pair(filename,file_metadata));
    fh2file.insert(std::make_pair(fh, filename));
    pointer.insert(std::make_pair(fh,0));
    return 0;
}

int POSIXMetadataManager::updateMetadata(FILE *fh) {
    opened_fh.insert(std::make_pair(fh, ++fildes));
    created_files[filename] = {true, mode, getuid(), getgid(),
                               created_files[filename].st_size, time(NULL),
                               created_files[filename].mtime , time(NULL)};
    fh2file.insert(std::make_pair(fh, filename));
    pointer.insert(std::make_pair(fh,0));
    return 0;
}
