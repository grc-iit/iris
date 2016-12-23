//
// Created by anthony on 12/10/16.
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "POSIXMapper.h"

std::vector<Key>
POSIXMapper::generateKeys(const char *name, size_t offset, size_t size) {
  std::vector<Key> keys;
  std::size_t baseKey = offset/MAX_OBJ_SIZE;
  std::size_t remainingOperationSize=size;
    int i=0;
    int keySize = sizeof(name)+sizeof(baseKey);
    Key key;
    while(remainingOperationSize!=0) {
      key.name = (char *) std::malloc((std::size_t) keySize);
      std::size_t baseOffset = ((baseKey + i) * MAX_OBJ_SIZE);
    std::sprintf(key.name, "%s_%ld", name, (baseKey + i));
    if (offset == baseOffset) {
      key.offset = 0;
      if (remainingOperationSize < MAX_OBJ_SIZE) {
        key.size = remainingOperationSize;
        remainingOperationSize =0;
      } else {
        key.size = MAX_OBJ_SIZE;
        remainingOperationSize -= MAX_OBJ_SIZE;
      }
      offset+=key.size;
    }else {
        key.offset = offset - baseOffset;
        key.size = (baseOffset + MAX_OBJ_SIZE) - offset;
        remainingOperationSize -= key.size;
        offset += key.size;
    }
#ifdef DEBUG
      std::cout<< "keyName : " << key.name << "\tOffset : " << key.offset <<"\tData Size : " << key.size <<std::endl;
#endif
    ++i;
    keys.push_back(key);
  }
  return keys;
}
