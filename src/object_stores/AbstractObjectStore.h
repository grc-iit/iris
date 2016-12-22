//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_ABSTRACTOBJECTSTORE_H
#define IRIS_ABSTRACTOBJECTSTORE_H


#include "../constants.h"

class AbstractObjectStore {
public:
    virtual int get(Key &key) = 0;

    virtual int put(Key &key) = 0;

    virtual int remove(Key &key) = 0;
};


#endif //IRIS_ABSTRACTOBJECTSTORE_H
