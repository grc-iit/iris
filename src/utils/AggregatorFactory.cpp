/******************************************************************************
*include files
******************************************************************************/
#include "AggregatorFactory.h"
#include "../constants.h"
#include "FileSystemAggregator.h"
#include "ObjectStoreAggregator.h"

/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<AggregatorFactory> AggregatorFactory::instance = nullptr;
/******************************************************************************
*Constructor
******************************************************************************/
AggregatorFactory::AggregatorFactory() {}
/******************************************************************************
*Destructor
******************************************************************************/
AggregatorFactory::~AggregatorFactory() {}
/******************************************************************************
*Gettters and setters
******************************************************************************/
std::shared_ptr<AbstractAggregator> AggregatorFactory::getAggregator(const char
                                                              *name) {
  AbstractAggregator* aggregatorInstance= nullptr;
  if(strcmp(name,FILESYSTEM_AGGREGATOR)==0){
    aggregatorInstance=new FileSystemAggregator();
  }
  else if(strcmp(name,OBJECTSTORE_AGGREGATOR)==0){
    aggregatorInstance=new ObjectStoreAggregator();
  }
  else return nullptr;
  return std::shared_ptr<AbstractAggregator>(aggregatorInstance);
}




