/******************************************************************************
*include files
******************************************************************************/
#include "PrefetcherFactory.h"
#include "../constants.h"
#include "FileSystemPrefetcher.h"
#include "ObjectStorePrefetcher.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<PrefetcherFactory> PrefetcherFactory::instance = nullptr;
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
std::shared_ptr<PrefetcherFactory> PrefetcherFactory::getInstance() {
  PrefetcherFactory::instance = nullptr;
  if(instance== nullptr){
    instance=std::shared_ptr<PrefetcherFactory>(new PrefetcherFactory());
  }
  return instance;
}
std::shared_ptr<AbstractPrefetcher> PrefetcherFactory::getPrefetcher(const char *name) {
  AbstractPrefetcher* prefetcherInstance= nullptr;
  if(name == FILESYSTEM_PREFETCHER){
    prefetcherInstance=new FileSystemPrefetcher();
  }
  else if(name == OBJECTSTORE_PREFETCHER){
    prefetcherInstance=new ObjectStorePrefetcher();
  }
  else return nullptr;
  return std::shared_ptr<AbstractPrefetcher>(prefetcherInstance);
}


