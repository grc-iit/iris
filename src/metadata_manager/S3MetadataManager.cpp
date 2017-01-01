//
// Created by anthony on 12/10/16.
//

#include "S3MetadataManager.h"
#include "../API.h"
#include "../utils/FileSystemAggregator.h"

void S3MetadataManager::switchActiveMemTable() {
  if (asyncSortTable.valid()){
    if(asyncSortTable.get() == FLUSH_SORTEDTABLES){
      auto apiInstance = API::getInstance();
      auto fileSystemAggregator = std::static_pointer_cast<FileSystemAggregator>
          (apiInstance->getAggregatorFactory()->getAggregator
              (FILESYSTEM_AGGREGATOR));
      fileSystemAggregator->collectAndFlush(sortedTables);
    }
  }
  activeMemTable.push_front(activeMemTable.back());
  asyncSortTable = std::async(std::launch::async,
                              &sortMemTable,
                              this,
                              activeMemTable.back());
}

int S3MetadataManager::sortMemTable(std::unordered_map<Key, Container> &memTable) {
  std::map<Key, Container> sortedTable = std::map<Key, Container>
      (memTable.begin(), memTable.end());
  sortedTables.emplace_back(sortedTable);
  if(sortedTables.size() == MAX_NUM_SORTED_TABLES) return FLUSH_SORTEDTABLES;
  else return OPERATION_SUCCESSFUL;
}

int S3MetadataManager::getFileHandler(Container &container) {
  auto apiInstance = API::getInstance();
  auto s3Mapper = std::static_pointer_cast<S3Mapper>
      (apiInstance->getMapperFactory()->getMapper(S3_MAPPER));
  auto iterator = s3Mapper->getContainerList().find(container.getFilename());
  if(iterator == s3Mapper->getContainerList().end()) return FH_DOES_NOT_EXIST;
  container.setFh(iterator->second.getFh());
  return OPERATION_SUCCESSFUL;
}



