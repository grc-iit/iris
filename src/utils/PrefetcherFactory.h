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
* File PrefetcherFactory.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_PREFETCHERFACTORY_H
#define IRIS_PREFETCHERFACTORY_H
/******************************************************************************
*include files
******************************************************************************/
#include "AbstractPrefetcher.h"
#include <memory>

class PrefetcherFactory {
private:
/******************************************************************************
*Constructor
******************************************************************************/
  PrefetcherFactory();

/******************************************************************************
*Private members
******************************************************************************/
  static std::shared_ptr<PrefetcherFactory> instance;

public:
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~PrefetcherFactory();
/******************************************************************************
*Gettters and setters
******************************************************************************/
  inline static std::shared_ptr<PrefetcherFactory> getInstance(){
    return instance== nullptr ? instance=std::shared_ptr<PrefetcherFactory>
        (new PrefetcherFactory())
                              : instance;
  }
  std::shared_ptr<AbstractPrefetcher> getPrefetcher(const char* name);
};


#endif //IRIS_PREFETCHERFACTORY_H
