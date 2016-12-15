/******************************************************************************
*include files
******************************************************************************/
#include "PrefetcherFactory.h"
#include "../Constants.h"
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
PrefetcherFactory *PrefetcherFactory::getInstance() {
  if(instance== nullptr){
    instance=new PrefetcherFactory();
  }
  return instance;
}
AbstractPrefetcher* PrefetcherFactory::getPrefetcher(const char *name) {
  AbstractPrefetcher* prefetcherInstance= nullptr;
  if(name == FILESYSTEM_PREFETCHER){
    prefetcherInstance=new FileSystemPrefetcher();
  }
  else if(name == OBJECTSTORE_PREFETCHER){
    prefetcherInstance=new ObjectStorePrefetcher();
  }
  else return nullptr;
  return prefetcherInstance;
}

