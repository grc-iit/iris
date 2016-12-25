/*******************************************************************************
* File MetadataManagerFactory.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_METADATAMANAGERFACTORY_H
#define IRIS_METADATAMANAGERFACTORY_H
/******************************************************************************
*include files
******************************************************************************/
#include <memory>
#include <unordered_map>
#include "IrisMetadataManager.h"
/******************************************************************************
*Class
******************************************************************************/
class MetadataManagerFactory {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  std::unordered_map<const char*, std::shared_ptr<IrisMetadataManager>>
      metadataManagerMap;
  static std::shared_ptr<MetadataManagerFactory> instance;
/******************************************************************************
*Constructor
******************************************************************************/
  MetadataManagerFactory();
public:
/******************************************************************************
*Getters and setters
******************************************************************************/
  static std::shared_ptr<MetadataManagerFactory> getInstance();
  std::shared_ptr<IrisMetadataManager> getMetadataManager(const char* name);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~MetadataManagerFactory();
};


#endif //IRIS_METADATAMANAGERFACTORY_H
