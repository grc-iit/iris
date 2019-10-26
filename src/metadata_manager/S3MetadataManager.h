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

#ifndef IRIS_S3METADATAMANAGER_H
#define IRIS_S3METADATAMANAGER_H

#include <unordered_map>
#include "IrisMetadataManager.h"
#include "../constants.h"

class S3MetadataManager: public IrisMetadataManager {
private:
  std::unordered_map<std::string, FILE *> filenameToFile;
public:
  S3MetadataManager(){
    filenameToFile = std::unordered_map<std::string, FILE *>();
  }
  int getFileHandler(VirtualFile & virtualFile);
  int updateFileHandler(VirtualFile & virtualFile);
  int deleteFileHandler(VirtualFile &virtualFile);
};


#endif //IRIS_S3METADATAMANAGER_H
