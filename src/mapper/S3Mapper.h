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
//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_S3MAPPER_H
#define IRIS_S3MAPPER_H

#include <vector>
#include <unordered_map>
#include <memory>
#include "AbstractMapper.h"
#include "../constants.h"

class S3Mapper: public AbstractMapper {
private:
  static std::shared_ptr<S3Mapper> instance;
  std::unordered_map<std::string, VirtualFile> filenameToVirtualfile;
  std::unordered_map<std::string, size_t > keyToHash;
  size_t hashKey(std::string keyName,std::size_t objectSize);
  size_t currentFileSize;
  std::size_t currentHash;
  S3Mapper() {
    filenameToVirtualfile = std::unordered_map<std::string, VirtualFile>();
      keyToHash = std::unordered_map<std::string, size_t >();
    currentFileSize=0;
    currentHash=0;
  }
public:
  VirtualFile generateFileForGet(std::string keyName);
    VirtualFile generateFileForPut(std::string keyName,std::size_t
    objectSize);
  static std::shared_ptr<S3Mapper> getInstance() {
    return instance == nullptr ? instance =
                                     std::shared_ptr<S3Mapper>(new S3Mapper())
                               : instance;
  }
};

#endif //IRIS_S3MAPPER_H
