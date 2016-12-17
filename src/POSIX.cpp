//
// Created by anthony on 12/10/16.
//

#include <cstring>
#include "POSIX.h"

/******************************************************************************
*fopen
******************************************************************************/
FILE *fopen(const char *filename, const char *mode) {
    std::unique_ptr<API> apiInstance = API::getInstance();
    std::unique_ptr<POSIXMetadataManager> posixMetadataManager =
            (POSIXMetadataManager*)apiInstance->getMetadataManagerFactory()->
                    getMetadataManager(POSIX_METADATA_MANAGER);

    if(std::strlen(filename) > MAX_FILENAME_LENGTH){
        fprintf(stderr, "ERROR! File name too long!\n");
        return NULL;
    }

    FILE* fh;
    if(!posixMetadataManager->checkIfFileCreated(filename)){
        fh = fmemopen(NULL, FILE_BUFFER_CAPACITY, mode);
        if (fh == NULL){
            printf("fopen() error: %s\n", strerror(errno));
            return NULL;
        }
        posixMetadataManager->createMetadata(fh);
    }
    else{

        fh = fmemopen(NULL, FILE_BUFFER_CAPACITY, mode);
        if (fh == NULL){
            printf("fmemopen() error: %s\n", strerror(errno));
            return NULL;
        }
        posixMetadataManager->updateMetadata(fh);
    }
    return fh;
}
