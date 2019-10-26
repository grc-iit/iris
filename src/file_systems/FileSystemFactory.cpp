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
#include <cstring>
#include <memory>
#include "FileSystemFactory.h"
#include "../constants.h"
#include "PVFS2Client.h"

/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<FileSystemFactory> FileSystemFactory::instance = nullptr;

std::shared_ptr<AbstractFileSystem>
FileSystemFactory::getFileSystem(const char *name) {
  std::shared_ptr<AbstractFileSystem> fileSystemClient;
  if (strcmp(name,PVFS2_CLIENT)==0) {
    fileSystemClient = std::shared_ptr<PVFS2Client>(new PVFS2Client());
  }
  return fileSystemClient;
}
