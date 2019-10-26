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
/*******************************************************************************
* File POSIXMetadataManager.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_POSIXMETADATAMANAGER_H
#define IRIS_POSIXMETADATAMANAGER_H
/******************************************************************************
*include files
******************************************************************************/
#include <unistd.h>
#include <ctime>
#include <unordered_map>
#include "IrisMetadataManager.h"
/******************************************************************************
*Class
******************************************************************************/
class POSIXMetadataManager: public IrisMetadataManager {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  /*filename plus metadata information*/
  struct Stat {
    bool            opened;     /*flag if the file is opened*/
    const char*     mode;       /* mode */
    uid_t           st_uid;     /* user ID of owner */
    gid_t           st_gid;     /* group ID of owner */
    size_t          st_size;    /* total size, in bytes */
    time_t          atime;      /* time of last access */
    time_t          mtime;      /* time of last modification */
    time_t          ctime;      /* time of last status change */
  };
  std::unordered_map<const char *, Stat> created_files;
  /*file handler to filename mapping*/
  std::unordered_map<FILE *, const char *> fh2filename;
  /*file position for every file handler that is opened*/
  std::unordered_map<FILE *, long int> pointer;

public:
/******************************************************************************
*Constructor
******************************************************************************/
  POSIXMetadataManager();
/******************************************************************************
*Interface
******************************************************************************/
  bool checkIfFileExists(const char *filename);
  bool checkIfFileIsOpen(const char *filename);
  const char * getFilename(FILE *fh);
  long int getFilesize(const char * filename);
  int createMetadata(FILE * fh, const char * filename, const char* mode);
  int updateMetadataOnOpen(FILE * fh, const char * filename, const char* mode);
  int updateMetadataOnClose(FILE * fh, const char * filename);
  int updateMetadataOnRead(FILE * fh, std::size_t operationSize);
  int updateMetadataOnWrite(FILE *fh, std::size_t operationSize);
  int updateFpPosition(FILE * fh, long int offset, int origin, const char*
  filename);
  long int getFpPosition(FILE * fh);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~POSIXMetadataManager();
};

#endif //IRIS_POSIXMETADATAMANAGER_H
