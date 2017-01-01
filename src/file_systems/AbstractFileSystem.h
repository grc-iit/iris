/*******************************************************************************
* File AbstractFileSystem.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_ABSTRACTFILESYSTEM_H
#define IRIS_ABSTRACTFILESYSTEM_H
/******************************************************************************
*include files
******************************************************************************/
#include "../constants.h"
/******************************************************************************
*Class
******************************************************************************/
class AbstractFileSystem {
public:
/******************************************************************************
*Interface
******************************************************************************/
  virtual int fopen(Container &virtualFile) = 0;
  virtual int fclose(Container &virtualFile) = 0;
  virtual int fread(Container &virtualFile) = 0;
  virtual int fwrite(Container &virtualFile) = 0;
  virtual int fseek(Container &virtualFiley) = 0;
};

#endif //IRIS_ABSTRACTFILESYSTEM_H



