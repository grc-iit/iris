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

#include "S3Mapper.h"
#include "../constants.h"

/******************************************************************************
*Initialization of static members
******************************************************************************/
std::shared_ptr<S3Mapper> S3Mapper::instance = nullptr;

VirtualFile S3Mapper::generateFileForPut(std::string keyName, std::size_t
objectSize) {
    //first we get the filename from hash function
    std::size_t hash = hashKey(keyName, objectSize);
    std::string filename = "tmpfile_"
                           + std::to_string(hash)
                           + ".dat";
    VirtualFile virtualFile;
    auto iterator = filenameToVirtualfile.find(filename);
    if (iterator == filenameToVirtualfile.end()) {
        //if file is new create a new Virtual file and set the key parameters
        virtualFile = VirtualFile();
        virtualFile.setFilename(filename);
        virtualFile.setOffset(objectSize);
        virtualFile.setSize(objectSize);
        Key key;
        key.size=objectSize;
        key.offset=0;
        key.name=keyName.c_str();
        virtualFile.getKeys().insert(std::make_pair(keyName,key));
    } else {
        // if file name exist then update the Virtual file with new parameters
        virtualFile = iterator->second;
        Key key;
        key.size=objectSize;
        key.offset=virtualFile.getOffset();
        key.name=keyName.c_str();
        virtualFile.setSize(virtualFile.getSize() + objectSize);
        virtualFile.setOffset(virtualFile.getOffset()+objectSize);
        auto keyNameIterator=virtualFile.getKeys().find(keyName);

        if(keyNameIterator==virtualFile.getKeys().end()){
            virtualFile.getKeys().insert(std::make_pair(keyName,key));
        }else{
            virtualFile.getInvalidKeys().insert(std::make_pair(keyName,keyNameIterator->second));
            virtualFile.setSize(virtualFile.getSize() - keyNameIterator->second.size);
            virtualFile.getKeys()[keyName] = key;
            //virtualFile.getKeys().insert(std::make_pair(keyName,key));
        }
        filenameToVirtualfile.erase(filename);
    }
    if (currentFileSize + objectSize >= MAX_VF_SIZE) {
        virtualFile.setFilled(true);
    }
    currentFileSize = virtualFile.getSize();
    currentHash = hash;
    filenameToVirtualfile.insert(std::make_pair(filename, virtualFile));
    return virtualFile;
}

VirtualFile S3Mapper::generateFileForGet(std::string keyName) {
    //first we get the filename from hash function
    auto keyIterator = keyToHash.find(keyName);
    std::size_t hash;
    if (keyIterator == keyToHash.end()) {
        //TODO: key not found
    }else{
        hash=keyIterator->second;
    }
    std::string filename = "tmpfile_"
                           + std::to_string(hash)
                           + ".dat";
    VirtualFile virtualFile;
    auto iterator = filenameToVirtualfile.find(filename);
    if (iterator == filenameToVirtualfile.end()) {
        //TODO: throw key not found
    } else {
        // if file name exist then update the Virtual file with new parameters
        virtualFile = iterator->second;
        auto keyListIterator=virtualFile.getKeys().find(keyName);
        if(keyListIterator==virtualFile.getKeys().end()){
            //TODO:throw key not found
        }
    }
    return virtualFile;
}

size_t S3Mapper::hashKey(std::string keyName, std::size_t
objectSize) {
    auto keyIterator = keyToHash.find(keyName);
    std::size_t hash;
    if (keyIterator != keyToHash.end()) {
        hash = keyIterator->second;
    } else if (currentFileSize + objectSize <= MAX_VF_SIZE && currentHash!=0) {
        return currentHash;
    } else {
        hash = SEED;
        for (auto s: keyName) {
            hash = hash * 101 + s++;
        }
        keyToHash.insert(std::make_pair(keyName,hash));
    }
    return hash;
}



