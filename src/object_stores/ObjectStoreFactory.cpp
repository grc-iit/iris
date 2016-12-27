#include "ObjectStoreFactory.h"
#include "HyperdexClient.h"
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<ObjectStoreFactory> ObjectStoreFactory::instance = nullptr;
/******************************************************************************
*Constructors
******************************************************************************/
ObjectStoreFactory::ObjectStoreFactory() {}
/******************************************************************************
*Destructor
******************************************************************************/
ObjectStoreFactory::~ObjectStoreFactory() {}
/******************************************************************************
*Getters and setters
******************************************************************************/
std::shared_ptr<AbstractObjectStore> ObjectStoreFactory::getObjectStore(const
                                                                        char* name) {
  std::shared_ptr<AbstractObjectStore> objectStoreClient;
  if (strcmp(name,HYPERDEX_CLIENT)==0) {
    objectStoreClient =
        std::static_pointer_cast<HyperdexClient>(HyperdexClient::getInstance());
  }
  return objectStoreClient;
}


