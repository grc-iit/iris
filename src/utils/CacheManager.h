//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_CACHEMANAGER_H
#define IRIS_CACHEMANAGER_H


class CacheManager {
private:
    static CacheManager* instance;
    CacheManager(){

    }
public:
    static CacheManager* getInstance();

};


#endif //IRIS_CACHEMANAGER_H
