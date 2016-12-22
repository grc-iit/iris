//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_POSIXMAPPER_H
#define IRIS_POSIXMAPPER_H


#include <vector>
#include "AbstractMapper.h"
#include "../constants.h"

class POSIXMapper: public AbstractMapper {
private:

public:
  std::vector<Key> generateKeys(const char *name, size_t offset,
                                size_t size);
};




#endif //IRIS_POSIXMAPPER_H
