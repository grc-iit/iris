/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
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
#ifdef DEBUG2
    std::cout << "keyName : " << key.name << "\tOffset : " << key.offset
     <<"\tData Size : " << key.size << std::endl;
#endif
  }
  return keys;
}
