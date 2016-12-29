/******************************************************************************
*include files
******************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "POSIXMapper.h"
/******************************************************************************
*Functions
******************************************************************************/
std::vector<Key>
POSIXMapper::generateKeys(const char *name, long int offset, size_t size) {
  std::vector<Key> keys;
  std::size_t baseKey = offset/MAX_OBJ_SIZE;
  std::size_t remainingOperationSize=size;
  int i=0;
  std::size_t keySize = strlen(name)+ sizeof(char) + sizeof(baseKey);
  Key key;
  while(remainingOperationSize!=0) {
    key.name = new char[keySize];
    std::size_t baseOffset = ((baseKey + i) * MAX_OBJ_SIZE);
    std::sprintf((char*)key.name, "%s_%ld", name, (baseKey + i));
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
    ++i;
    keys.push_back(key);
#ifdef DEBUG
    std::cout << "keyName : " << key.name << "\tOffset : " << key.offset
     <<"\tData Size : " << key.size << std::endl;
#endif
  }
  return keys;
}
