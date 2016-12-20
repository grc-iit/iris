//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_HYPERDEXCLIENT_H
#define IRIS_HYPERDEXCLIENT_H


#include <memory>
#include <vector>
#include "AbstractObjectStore.h"

class HyperdexClient : public AbstractObjectStore {
    static std::unique_ptr<HyperdexClient> instance;

    HyperdexClient() {

    }

public:
    static std::unique_ptr<HyperdexClient> getInstance();

    int get(Key key, void *&data) override;

    int put(Key key, void *data) override;

    int remove(Key key) override;

    int gets(std::vector<Key> key, std::vector<void*> &data);
};


#endif //IRIS_HYPERDEXCLIENT_H
