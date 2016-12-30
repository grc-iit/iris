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
  auto pvfsClient = std::static_pointer_cast<PVFS2Client>
      (apiInstance->getFileSystemFactory()->getFileSystem(PVFS2_CLIENT));

  VirtualFile virtualFile= s3Mapper->generateFiles(key,key_sz);
  //todo: error checks
  pvfsClient->fopen(virtualFile);
  pvfsClient->fread(virtualFile);
  hyperdex_client_attribute* attributes[1];
  attributes[0]->value = (const char *) virtualFile.getData();
  attributes[0]->value_sz=virtualFile.getSize()-virtualFile.getOffset();
  attrs=attributes;
  pvfsClient->fclose(virtualFile);
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

  auto pvfsClient = std::static_pointer_cast<PVFS2Client>
      (apiInstance->getFileSystemFactory()->getFileSystem(PVFS2_CLIENT));
  VirtualFile virtualFile= s3Mapper->generateFiles(key,key_sz);
  virtualFile.setData((void *) attrs[0].value);
  pvfsClient->fopen(virtualFile);
  pvfsClient->fwrite(virtualFile);
  pvfsClient->fclose(virtualFile);
  return -1;
}
