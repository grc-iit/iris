//
// Created by anthony on 12/10/16.
//

#include "FileSystemAggregator.h"
#include "../file_systems/PVFS2Client.h"
#include "../API.h"


int FileSystemAggregator::collectAndFlush(
    std::vector<std::map<Key, Container>> &sortedTables) {
  auto apiInstance = API::getInstance();
  auto pvfs2Client = std::static_pointer_cast<PVFS2Client>
      (apiInstance->getFileSystemFactory()->getFileSystem(PVFS2_CLIENT));
  while(sortedTables.size() != 0){
    for(auto key: sortedTables.front()){
      if(pvfs2Client->fopen(key.second) == OPERATION_SUCCESSFUL){
        pvfs2Client->fseek(key.second);
        pvfs2Client->fwrite(key.second);
      }

    }
  }


  return 0;
}
