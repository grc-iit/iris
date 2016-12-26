/*******************************************************************************
* File CacheManager.h
*
* Goal:
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
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
#include "Buffer.h"

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
  typedef std::list<const char *> LI;
  typedef std::pair<void *, LI::iterator> PII;
  typedef std::unordered_map<const char *, PII> HIPII;
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
  static std::shared_ptr<CacheManager> getInstance();
/******************************************************************************
*Functions
******************************************************************************/
  int isCached(Key &key);
  int addToCache(Key &key);
/******************************************************************************
*Destructor
******************************************************************************/
  virtual ~CacheManager();
};


#endif //IRIS_CACHEMANAGER_H
