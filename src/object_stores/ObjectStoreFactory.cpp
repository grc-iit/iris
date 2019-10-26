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


