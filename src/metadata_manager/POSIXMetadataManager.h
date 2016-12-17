//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_POSIXMETADATAMANAGER_H
#define IRIS_POSIXMETADATAMANAGER_H


#include <unistd.h>
#include <ctime>
#include <unordered_map>
#include "AbstractMetadataManager.h"

class POSIXMetadataManager: public AbstractMetadataManager {
private:
    int fildes;//file descriptors

    struct Stat {
        bool            opened;     /*flag if the file is opened*/
        const char*     mode;       /* mode */
        uid_t           st_uid;     /* user ID of owner */
        gid_t           st_gid;     /* group ID of owner */
        off_t           st_size;    /* total size, in bytes */
        time_t          atime;      /* time of last access */
        time_t          mtime;      /* time of last modification */
        time_t          ctime;      /* time of last status change */
    };

    /*filename plus metadata information*/
    std::unordered_map<const char *, Stat> created_files;
    /*active file handler and file descriptor according to the opened file*/
    std::unordered_map<FILE *, int> opened_fh;
    /*file handler to filename mapping*/
    std::unordered_map<FILE *, const char *> fh2file;
    /*file position for every file handler that is opened*/
    std::unordered_map<FILE *, long int> pointer;
public:
    bool checkIfFileCreated(const char *filename);
    int createMetadata(FILE * fh);
    int updateMetadata(FILE * fh);

};


#endif //IRIS_POSIXMETADATAMANAGER_H
