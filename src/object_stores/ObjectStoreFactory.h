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
/*******************************************************************************
* File ObjectStoreFactory.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_OBJECTSTOREFACTORY_H
#define IRIS_OBJECTSTOREFACTORY_H
/******************************************************************************
*include files
******************************************************************************/
#include <memory>
#include "AbstractObjectStore.h"
/******************************************************************************
*Class
******************************************************************************/
class ObjectStoreFactory {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  static std::shared_ptr<ObjectStoreFactory> instance;
/******************************************************************************
*Constructors
******************************************************************************/
  ObjectStoreFactory();
public:
/******************************************************************************
*Getters and setters
******************************************************************************/
  inline static std::shared_ptr<ObjectStoreFactory> getInstance(){
    return instance == nullptr ? instance = std::shared_ptr<ObjectStoreFactory>
        (new ObjectStoreFactory())
                               : instance;
  }
  std::shared_ptr<AbstractObjectStore> getObjectStore(const char* name);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~ObjectStoreFactory();
};


#endif //IRIS_OBJECTSTOREFACTORY_H
