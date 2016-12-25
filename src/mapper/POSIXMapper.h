/*******************************************************************************
* File POSIXMapper.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_POSIXMAPPER_H
#define IRIS_POSIXMAPPER_H
/******************************************************************************
*include files
******************************************************************************/
#include <vector>
#include "AbstractMapper.h"
#include "../constants.h"
/******************************************************************************
*Class
******************************************************************************/
class POSIXMapper: public AbstractMapper {
public:
/******************************************************************************
*Functions
******************************************************************************/
  std::vector<Key> generateKeys(const char *name, long int offset,
                                size_t size);
};
#endif //IRIS_POSIXMAPPER_H
