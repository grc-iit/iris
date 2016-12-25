/*******************************************************************************
* File AbstractObjectStore.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_ABSTRACTOBJECTSTORE_H
#define IRIS_ABSTRACTOBJECTSTORE_H
/******************************************************************************
*include files
******************************************************************************/
#include "../constants.h"
/******************************************************************************
*Class
******************************************************************************/
class AbstractObjectStore {
public:
/******************************************************************************
*Interface
******************************************************************************/
  virtual int get(Key &key) = 0;
  virtual int put(Key &key) = 0;
  virtual int remove(Key &key) = 0;
};

#endif //IRIS_ABSTRACTOBJECTSTORE_H
