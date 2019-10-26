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

#include "S3MetadataManager.h"

int S3MetadataManager::getFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()) return FH_DOES_NOT_EXIST;
  virtualFile.setFh(iterator->second);
  return OPERATION_SUCCESSFUL;
}

int S3MetadataManager::updateFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()){
    filenameToFile.insert(std::make_pair(virtualFile.getFilename(),
                                         virtualFile.getFh()));
  }
  else{
    filenameToFile[iterator->first] = virtualFile.getFh();
  }
  return OPERATION_SUCCESSFUL;
}

int S3MetadataManager::deleteFileHandler(VirtualFile &virtualFile) {
  auto iterator = filenameToFile.find(virtualFile.getFilename());
  if(iterator == filenameToFile.end()) return FH_DOES_NOT_EXIST;
  filenameToFile.erase(iterator->first);
  return OPERATION_SUCCESSFUL;
}
