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
  if(strcmp(name,FILESYSTEM_PREFETCHER)==0){
    prefetcherInstance=new FileSystemPrefetcher();
  }
  else if(strcmp(name,OBJECTSTORE_PREFETCHER)==0){
    prefetcherInstance=new ObjectStorePrefetcher();
  }
  else return nullptr;
  return std::shared_ptr<AbstractPrefetcher>(prefetcherInstance);
}


