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
* File CacheManager.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
******************************************************************************/
#ifndef IRIS_CACHEMANAGER_H
#define IRIS_CACHEMANAGER_H
/******************************************************************************
*include files
******************************************************************************/
#include <memory>
#include <vector>
#include <unordered_map>
#include <list>
#include "../constants.h"
#include "tools/Buffer.h"

/******************************************************************************
*Class
******************************************************************************/
class CacheManager {
private:
/******************************************************************************
*Variables and members
******************************************************************************/
  static std::shared_ptr<CacheManager> instance;
  int cacheCapacity;

  typedef std::list<std::string> LI;
  typedef std::pair<void *, LI::iterator> PII;
  typedef std::unordered_map<std::string, PII> HIPII;
  HIPII cacheMap;
  LI lruList;

  void refreshLRU(HIPII::iterator cacheline);
/******************************************************************************
*Constructor
******************************************************************************/
  CacheManager();
public:
/******************************************************************************
*Getters and setters
******************************************************************************/
  inline static std::shared_ptr<CacheManager> getInstance(){
    return instance== nullptr ? instance=std::shared_ptr<CacheManager>
        (new CacheManager())
                              : instance;
  }
/******************************************************************************
*Functions
******************************************************************************/
  int isCached(Key &key);
  int addToCache(Key &key);
  int addRangeToCache(std::vector<Key> keys);

/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~CacheManager();
};


#endif //IRIS_CACHEMANAGER_H
