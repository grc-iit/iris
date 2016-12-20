//
// Created by anthony on 12/10/16.
//

#include "HyperdexClient.h"

std::unique_ptr<HyperdexClient> HyperdexClient::getInstance() {
    if (instance == nullptr) {
        instance = new HyperdexClient();
    }
    return instance;
}

int HyperdexClient::get(Key key, void *&data) {
    return 0;
}

int HyperdexClient::put(Key key, void *data) {
    return 0;
}

int HyperdexClient::remove(Key key) {
    return 0;
}
