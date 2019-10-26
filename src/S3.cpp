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

#include "S3.h"
#include "file_systems/PVFS2Client.h"

int64_t iris::hyperdex_client_get(struct hyperdex_client* client,
                            const char* space,
                            const char* key,
                            size_t key_sz,
                            enum hyperdex_client_returncode* status,
                            const struct hyperdex_client_attribute** attrs,
                            size_t* attrs_sz){
  auto apiInstance = API::getInstance();
  auto s3Mapper = std::static_pointer_cast<S3Mapper>
      (apiInstance->getMapperFactory()->getMapper(S3_MAPPER));
  auto pvfs2Client = std::static_pointer_cast<PVFS2Client>
      (apiInstance->getFileSystemFactory()->getFileSystem(PVFS2_CLIENT));

  VirtualFile virtualFile= s3Mapper->generateFileForGet(key);
  //todo: error checks
  pvfs2Client->fopen(virtualFile);
  pvfs2Client->fread(virtualFile);
  auto keyIterator=virtualFile.getKeys().find(key);
  if(keyIterator==virtualFile.getKeys().end()){
    //TODO:throw error
  }else{
    Key keyObject=keyIterator->second;
    hyperdex_client_attribute* attributes[1];
    attributes[0]->value=new char[keyObject.size];
    memcpy((void *) attributes[0]->value, (char*)virtualFile.getData() +
        keyObject.offset, keyObject.size);
    attributes[0]->value_sz=keyObject.size;
    attrs=(const hyperdex_client_attribute**)attributes;//fixme
  }
  pvfs2Client->fclose(virtualFile);
  return -1;
}

int64_t iris::hyperdex_client_put(struct hyperdex_client *client,
                                  const char *space, const char *key,
                                  size_t key_sz,
                                  const struct hyperdex_client_attribute *attrs,
                                  size_t attrs_sz,
                                  enum hyperdex_client_returncode *status) {
  auto apiInstance = API::getInstance();
  auto s3Mapper = std::static_pointer_cast<S3Mapper>
      (apiInstance->getMapperFactory()->getMapper(S3_MAPPER));
  auto pvfs2Client = std::static_pointer_cast<PVFS2Client>
      (apiInstance->getFileSystemFactory()->getFileSystem(PVFS2_CLIENT));

  VirtualFile virtualFile = s3Mapper->generateFileForPut(key,attrs[0].value_sz);
  auto keyIterator=virtualFile.getKeys().find(key);
  if(keyIterator==virtualFile.getKeys().end()){
    //TODO:throw error
  }else{
    Key keyObject=keyIterator->second;
    Buffer buffer=Buffer();
    buffer.append(virtualFile.getData(),virtualFile.getOffset()-keyObject.size);
    buffer.append(attrs[0].value,keyObject.size);
    virtualFile.setData(buffer.data());
  }
  pvfs2Client->fopen(virtualFile);
  pvfs2Client->fwrite(virtualFile);
  pvfs2Client->fclose(virtualFile);
  return -1;
}
