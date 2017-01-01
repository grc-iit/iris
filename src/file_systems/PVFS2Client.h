//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_PVFS2CLIENT_H
#define IRIS_PVFS2CLIENT_H


#include <unordered_map>
#include "AbstractFileSystem.h"
#include "../metadata_manager/MetadataManagerFactory.h"

class PVFS2Client: public AbstractFileSystem {
private:
  std::shared_ptr<MetadataManagerFactory> metadataManagerFactory;
public:
  virtual int fopen(Container &container) override;

  virtual int fclose(Container &container) override;

  virtual int fread(Container &container) override;

  virtual int fwrite(Container &container) override;

  virtual int fseek(Container &container) override;

  PVFS2Client() {
    metadataManagerFactory=MetadataManagerFactory::getInstance();
  }
};


#endif //IRIS_PVFS2CLIENT_H
