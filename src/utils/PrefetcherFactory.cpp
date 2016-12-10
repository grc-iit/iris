//
// Created by anthony on 12/10/16.
//

#include "PrefetcherFactory.h"
#include "../Constants.h"
#include "FileSystemPrefetcher.h"
#include "ObjectStorePrefetcher.h"

PrefetcherFactory *PrefetcherFactory::getInstance() {
    if(instance== nullptr){
        instance=new PrefetcherFactory();
    }
    return instance;
}

AbstractPrefetcher* PrefetcherFactory::getPrefetcher(const char *name) {
    AbstractPrefetcher* prefetcherInstance= nullptr;
    switch(name){
        case FILESYSTEM_PREFETCHER:
            prefetcherInstance=new FileSystemPrefetcher();
            break;
        case OBJECTSTORE_PREFETCHER:
            prefetcherInstance=new ObjectStorePrefetcher();
            break;

    }
    return prefetcherInstance;
}
