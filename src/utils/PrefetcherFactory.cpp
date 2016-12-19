/******************************************************************************
*include files
******************************************************************************/
#include <bits/unique_ptr.h>
#include "PrefetcherFactory.h"
#include "../constants.h"
#include "FileSystemPrefetcher.h"
#include "ObjectStorePrefetcher.h"
/******************************************************************************
*Constructor
******************************************************************************/
PrefetcherFactory::PrefetcherFactory() {}
/******************************************************************************
*Destructor
******************************************************************************/
PrefetcherFactory::~PrefetcherFactory() {}
/******************************************************************************
*Gettters and setters
******************************************************************************/
std::unique_ptr<PrefetcherFactory> PrefetcherFactory::getInstance() {
  if(instance== nullptr){
    instance=new PrefetcherFactory();
  }
  return instance;
}
std::unique_ptr<AbstractPrefetcher> PrefetcherFactory::getPrefetcher(const char *name) {
  std::unique_ptr<AbstractPrefetcher> prefetcherInstance= nullptr;
  if(name == FILESYSTEM_PREFETCHER){
    prefetcherInstance=new FileSystemPrefetcher();
  }
  else if(name == OBJECTSTORE_PREFETCHER){
    prefetcherInstance=new ObjectStorePrefetcher();
  }
  else return nullptr;
  return prefetcherInstance;
}

