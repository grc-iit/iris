//
// Created by anthony on 12/10/16.
//

#include <cstdlib>
#include "POSIXMapper.h"

std::vector<Key>
POSIXMapper::generateKeys(const char * name, size_t offset, size_t size) {
  std::vector<Key> keys;

  size_t base_key = offset/MAX_OBJ_SIZE;
  size_t remainingOperationSize=size;
  Key key;
  int i=0;
  int keySize = sizeof(name)+sizeof(base_key);
  key.name = (char *) std::malloc((size_t) keySize);
  while(remainingOperationSize!=0) {
    sprintf(key.name, "%s_%ld", name, (base_key + i));
    if (offset == ((base_key + i) * MAX_OBJ_SIZE)) {
      key.offset = 0;
      if (remainingOperationSize < MAX_OBJ_SIZE) {
        key.size = remainingOperationSize;
        remainingOperationSize =0;
      } else {
        key.size = MAX_OBJ_SIZE;
        remainingOperationSize -= MAX_OBJ_SIZE
      }
      offset+=key.size;
    }else{
      key.offset = offset-((base_key + i) * MAX_OBJ_SIZE);
      key.size = ((base_key + i+1)* MAX_OBJ_SIZE)-offset;
      remainingOperationSize-=key.size;
      offset+=key.size;
    }
    ++i;
    keys.push_back(key);
  }
  return keys;
}
