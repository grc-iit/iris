/*******************************************************************************
* File MapperFactory.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_MAPPERFACTORY_H
#define IRIS_MAPPERFACTORY_H
/******************************************************************************
*include files
******************************************************************************/
#include <memory>
#include "AbstractMapper.h"
/******************************************************************************
*Class
******************************************************************************/
class MapperFactory {
private:
/******************************************************************************
*Constructor
******************************************************************************/
  MapperFactory();
/******************************************************************************
*Private members
******************************************************************************/
  static std::shared_ptr<MapperFactory> instance;

public:
/******************************************************************************
*Gettters and setters
******************************************************************************/
  inline static std::shared_ptr<MapperFactory> getInstance(){
    return instance== nullptr ? instance = std::shared_ptr<MapperFactory>
        (new MapperFactory())
                              : instance;
  }
  std::shared_ptr<AbstractMapper> getMapper(const char* name);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~MapperFactory();
};


#endif //IRIS_MAPPERFACTORY_H
