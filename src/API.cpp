
#include "API.h"

static API *API::getInstance() {
    if(instance== nullptr){
        instance=new API();
    }
    return instance;
}

CacheManager *API::getCacheManager() {
    return cacheManager;
}





