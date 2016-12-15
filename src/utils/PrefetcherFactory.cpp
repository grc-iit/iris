//
// Created by anthony on 12/10/16.
//

#include "PrefetcherFactory.h"
#include "../Constants.h"
#include "FileSystemPrefetcher.h"
#include "ObjectStorePrefetcher.h"


PrefetcherFactory::PrefetcherFactory() {}
PrefetcherFactory::~PrefetcherFactory() {}


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

