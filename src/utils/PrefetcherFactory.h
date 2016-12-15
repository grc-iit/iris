//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_PREFETCHERFACTORY_H
#define IRIS_PREFETCHERFACTORY_H


#include "AbstractPrefetcher.h"

class PrefetcherFactory {
private:
  static PrefetcherFactory* instance;
  PrefetcherFactory();
  virtual ~PrefetcherFactory();

public:
  static PrefetcherFactory* getInstance();
  AbstractPrefetcher* getPrefetcher(const char* name);
};


#endif //IRIS_PREFETCHERFACTORY_H
