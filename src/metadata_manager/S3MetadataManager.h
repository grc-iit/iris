//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_S3METADATAMANAGER_H
#define IRIS_S3METADATAMANAGER_H

#include <unordered_map>
#include <list>
#include <map>
#include <vector>
#include "IrisMetadataManager.h"
#include "../constants.h"

class S3MetadataManager: public IrisMetadataManager {
private:
  std::unordered_map<Key, Container> workingMemTable, backupMemTable;
  std::list<std::unordered_map<Key, Container>> activeMemTable;
  std::vector<std::map<Key, Container>> sortedTables;
public:
  S3MetadataManager(){
    workingMemTable = std::unordered_map<Key, Container>();
    backupMemTable = std::unordered_map<Key, Container>();
    activeMemTable.push_front(backupMemTable);
    activeMemTable.push_front(workingMemTable);
    sortedTables = std::vector<std::map<Key, Container>>();
  }

  std::unordered_map<Key, Container> getActiveMemTable() {
    return activeMemTable.front();
  }

  void switchActiveMemTable();
  int sortMemTable(std::unordered_map<Key,Container> &memTable);
  int getFileHandler(Container &container);
  int updateFileHandler(Container &container);
  int deleteFileHandler(Container &container);
};


#endif //IRIS_S3METADATAMANAGER_H
