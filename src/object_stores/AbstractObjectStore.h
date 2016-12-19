//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_ABSTRACTOBJECTSTORE_H
#define IRIS_ABSTRACTOBJECTSTORE_H


#include "../Constants.h"

class AbstractObjectStore {
public:
    virtual int get(Key key, void *&data)= 0;

    virtual int put(Key key, void *data)= 0;

    virtual int remove(Key key)= 0;
};


#endif //IRIS_ABSTRACTOBJECTSTORE_H
