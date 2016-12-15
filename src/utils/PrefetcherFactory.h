/*******************************************************************************
* File PrefetcherFactory.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_PREFETCHERFACTORY_H
#define IRIS_PREFETCHERFACTORY_H
/******************************************************************************
*include files
******************************************************************************/
#include "AbstractPrefetcher.h"

class PrefetcherFactory {
private:
/******************************************************************************
*Constructor
******************************************************************************/
  PrefetcherFactory();
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~PrefetcherFactory();
/******************************************************************************
*Private members
******************************************************************************/
  static PrefetcherFactory* instance;

public:
/******************************************************************************
*Gettters and setters
******************************************************************************/
  static PrefetcherFactory* getInstance();
  AbstractPrefetcher* getPrefetcher(const char* name);
};


#endif //IRIS_PREFETCHERFACTORY_H
