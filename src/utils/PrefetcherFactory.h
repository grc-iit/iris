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
*Private members
******************************************************************************/
  static std::shared_ptr<PrefetcherFactory> instance;

public:
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~PrefetcherFactory();
/******************************************************************************
*Gettters and setters
******************************************************************************/
  static std::shared_ptr<PrefetcherFactory> getInstance();
  std::shared_ptr<AbstractPrefetcher> getPrefetcher(const char* name);
};


#endif //IRIS_PREFETCHERFACTORY_H
