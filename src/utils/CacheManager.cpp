//
// Created by anthony on 12/10/16.
//

#include "CacheManager.h"

CacheManager *CacheManager::getInstance() {
    if(instance== nullptr){
        instance=new CacheManager();
    }
    return instance;
}
