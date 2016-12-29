#include "HyperdexClient.h"
#include "../API.h"
#include "../utils/Timer.h"
#include <hyperdex/client.h>
#include <hyperdex/admin.h>
#include <future>

/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<HyperdexClient> HyperdexClient::instance = nullptr;

/******************************************************************************
*Constructors
******************************************************************************/
HyperdexClient::HyperdexClient() {
    cacheManager = CacheManager::getInstance();
    prefetcherFactory = PrefetcherFactory::getInstance();
    operationToKeyMap = std::unordered_map<int64_t, OperationData>();
    if (init() != OPERATION_SUCCESSFUL) {
        fprintf(stderr, "Hyperdex failed to start! Please check the configuration of"
                " your Hyperdex installation and restart coordinator and daemon.\n");
        exit(-1);
    }
}

/******************************************************************************
*Destructor
******************************************************************************/
HyperdexClient::~HyperdexClient() {}

/******************************************************************************
*Interface
******************************************************************************/
int HyperdexClient::get(Key &key) {
#ifdef TIMER
    Timer timer = Timer(); timer.startTime();
#endif
    int64_t op_id = 0, loop_id = 0;
    const struct hyperdex_client_attribute *attributes = 0;
    std::size_t attributes_sz = 0;
    enum hyperdex_client_returncode op_status, loop_status;
    op_id = hyperdex_client_get(hyperdexClient,
                                SPACE,
                                key.name,
                                strlen(key.name),
                                &op_status,
                                &attributes,
                                &attributes_sz);
    logRequest(op_id,GET_OPERATION,key,&attributes,&attributes_sz);
    int status=getKey(op_id,key);
    hyperdex_client_destroy_attrs(attributes, attributes_sz);
#ifdef TIMER
    timer.endTime(__FUNCTION__);
#endif
    return status;
}

int HyperdexClient::put(Key &key) {
#ifdef TIMER
    Timer timer = Timer(); timer.startTime();
#endif
    int status = 0;
    struct hyperdex_client_attribute attribute;
    enum hyperdex_client_returncode op_status, loop_status;
    int64_t op_id = 0, loop_id = 0;

    Key originalKey = key;
    Buffer dataBuffer;

    if (key.offset == 0) {
        if (key.size != MAX_OBJ_SIZE) {
            status = get(key);
            if (status == OPERATION_SUCCESSFUL && key.size > originalKey.size) {
                dataBuffer = Buffer(key.data, key.size);
                dataBuffer.assign(originalKey.data, originalKey.size);
                key.data = dataBuffer.data();
            }
        }
    } else {
        status = get(key);
        if (status == OPERATION_SUCCESSFUL) {
            if (key.size > originalKey.offset + originalKey.size) {
                std::memcpy((char *) key.data + originalKey.offset, originalKey.data,
                            originalKey.size);
            } else {
                dataBuffer = Buffer(key.data, originalKey.offset);
                dataBuffer.append(originalKey.data);
                key.data = dataBuffer.data();
            }
        }
    }
    /*Prepare parameters for th actual put call on Hyperdex*/
    std::size_t attribute_sz = 1;
    attribute.attr = ATTRIBUTE_NAME;
    attribute.datatype = HYPERDATATYPE_STRING;
    attribute.value = (const char *) key.data;
    attribute.value_sz = key.size;

    op_id = hyperdex_client_put(hyperdexClient,
                                SPACE,
                                key.name,
                                strlen(key.name),
                                &attribute,
                                attribute_sz,
                                &op_status);
    logRequest(op_id,PUT_OPERATION,key, nullptr,0);
    status=getKey(op_id,key);
#ifdef TIMER
    timer.endTime(__FUNCTION__);
#endif
    return status;
}

int HyperdexClient::getRange(std::vector<Key> &keys) {
#ifdef TIMER
    Timer timer = Timer(); timer.startTime();
#endif
    auto objectStorePrefetcher = std::static_pointer_cast<ObjectStorePrefetcher>
            (prefetcherFactory->getPrefetcher(OBJECTSTORE_PREFETCHER));

    int64_t op_id[keys.size()], loop_id;
    const struct hyperdex_client_attribute *attributes[keys.size()];
    std::size_t attributes_sz[keys.size()];
    enum hyperdex_client_returncode op_status[keys.size()], loop_status;
    std::vector<bool> loopCounter(keys.size(), false);
    std::future<int> asyncFetch;
    for (int i = 0; i < keys.size(); ++i) {
        if (cacheManager->isCached(keys[i]) != OPERATION_SUCCESSFUL) {
            if (i + 1 < keys.size())
                asyncFetch = std::async(std::launch::async,
                                         &ObjectStorePrefetcher::fetchKey,
                                        objectStorePrefetcher, keys[i+1]);
                op_id[i] = hyperdex_client_get(hyperdexClient,
                                               SPACE,
                                               keys[i].name,
                                               strlen(keys[i].name),
                                               &op_status[i],
                                               &attributes[i],
                                               &attributes_sz[i]);
            logRequest(op_id[i], GET_OPERATION, keys[i], &attributes[i], &attributes_sz[i]);
            loopCounter[i] = true;
            if(i+1 < keys.size()) asyncFetch.get();
        }
    }
    for (int i = 0; i < keys.size() && loopCounter[i]; i++) {
        int status = getKey(op_id[i], keys[i]);
    }


#ifdef TIMER
    timer.endTime(__FUNCTION__);
#endif
    return OPERATION_SUCCESSFUL;
}

int HyperdexClient::putRange(std::vector<Key> &keys) {
#ifdef TIMER
    Timer timer = Timer(); timer.startTime();
#endif
    int status[keys.size()];

    enum hyperdex_client_returncode op_status[keys.size()], loop_status;
    int64_t op_id[keys.size()], loop_id;
    Buffer dataBuffer[keys.size()];

    /*std::future<int> asyncAdd;
    if(CACHING_MODE == "ON") asyncAdd = std::async(std::launch::async,
                                                   &CacheManager::addRangeToCache,
                                                   cacheManager, keys);*/

    for (int i = 0; i < keys.size(); ++i) {
        Key originalKey = keys[i];
        if (keys[i].offset == 0) {
            if (keys[i].size != MAX_OBJ_SIZE) {
                status[i] = get(keys[i]);
                if (status[i] == OPERATION_SUCCESSFUL &&
                    keys[i].size > originalKey.size) {
                    dataBuffer[i] = Buffer(keys[i].data, keys[i].size);
                    dataBuffer[i].assign(originalKey.data, originalKey.size);
                    keys[i].data = dataBuffer[i].data();
                }
            }
        } else {
            status[i] = get(keys[i]);
            if (status[i] == OPERATION_SUCCESSFUL) {
                if (keys[i].size > originalKey.offset + originalKey.size) {
                    std::memcpy((char *) keys[i].data + originalKey.offset,
                                originalKey.data, originalKey.size);
                } else {
                    dataBuffer[i] = Buffer(keys[i].data, originalKey.offset);
                    dataBuffer[i].append(originalKey.data);
                    keys[i].data = dataBuffer[i].data();
                }
            }
        }
#ifdef DEBUG
        std::cout << "Put Key: " << keys[i].name << std::endl;
#endif /* DEBUG*/
        /*Prepare parameters for the actual put call on Hyperdex*/
        struct hyperdex_client_attribute attribute;
        std::size_t attribute_sz = 1;
        attribute.attr = ATTRIBUTE_NAME;
        attribute.datatype = HYPERDATATYPE_STRING;
        attribute.value = (const char *) keys[i].data;
        attribute.value_sz = keys[i].size;

        op_id[i] = hyperdex_client_put(hyperdexClient,
                                       SPACE,
                                       keys[i].name,
                                       strlen(keys[i].name),
                                       &attribute,
                                       attribute_sz,
                                       &op_status[i]);
        logRequest(op_id[i], PUT_OPERATION, keys[i], nullptr, 0);
    }
    for (int i = 0; i < keys.size(); i++) {
        int status = getKey(op_id[i], keys[i]);
    }
#ifdef DEBUG
    std::cout << "Put operation complete" << std::endl;
#endif /* DEBUG*/
    //if(CACHING_MODE == "ON") asyncAdd.get();
#ifdef TIMER
    timer.endTime(__FUNCTION__);
#endif
    return OPERATION_SUCCESSFUL;
}

int HyperdexClient::remove(Key &key) {
    return OPERATION_SUCCESSFUL;
}

/******************************************************************************
*Init function
******************************************************************************/
int HyperdexClient::init() {
#ifdef TIMER
    Timer timer = Timer(); timer.startTime();
#endif
    /* create the admin */
    struct hyperdex_admin *admin =
            hyperdex_admin_create(COORDINATOR, COORDINATOR_PORT);
    if (!admin) {
        fprintf(stderr, "Cannot create HyperDex ADMIN.\n");
        return HYPERDEX_ADMIN_CREATION_FAILED;
    }

    enum hyperdex_admin_returncode admin_status, loop_status;
    int64_t admin_id = 0, loop_id = 0;

    /*Removing previous spaces*/
    admin_id = hyperdex_admin_rm_space(admin, SPACE, &admin_status);
    loop_id = hyperdex_admin_loop(admin, -1, &loop_status);
    if (loop_id != admin_id || admin_status != HYPERDEX_ADMIN_SUCCESS) {
        fprintf(stderr, "Failed to remove old spaces!\n"
                        "ADMIN ID: %ld, STAT: %d, LOOP ID: %ld, STAT: %d\n",
                admin_id, admin_status, loop_id, loop_status);
    }

    /* add a space */
    admin_id = hyperdex_admin_add_space(admin, DESCRIPTION, &admin_status);
    loop_id = hyperdex_admin_loop(admin, -1, &loop_status);
    if (loop_id != admin_id || admin_status != HYPERDEX_ADMIN_SUCCESS) {
        fprintf(stderr, "Failed to create space!\n"
                        "ADMIN ID: %ld, STAT: %d, LOOP ID: %ld, STAT: %d\n",
                admin_id, admin_status, loop_id, loop_status);
    }
#ifdef DEBUG
    printf("Success creating space:{ %s }\n", SPACE);
#endif /* DEBUG*/

    /* Checking cluster stability*/
    admin_id = hyperdex_admin_wait_until_stable(admin, &admin_status);
    loop_id = hyperdex_admin_loop(admin, -1, &loop_status);
    if (loop_id != admin_id || admin_status != HYPERDEX_ADMIN_SUCCESS)
        fprintf(stderr, "Cluster not ready! Admin ID: %ld Status: %d \n", admin_id,
                admin_status);
#ifdef DEBUG
    printf("Cluster stable\n");
#endif /* DEBUG*/
    hyperdex_admin_destroy(admin);

    /* Setup the hyperdex client */
    hyperdexClient = hyperdex_client_create(COORDINATOR, COORDINATOR_PORT);
    /* make sure the client is OK */
    if (!hyperdexClient) {
        fprintf(stderr, "Cannot create HyperDex client.\n");
        return HYPERDEX_CLIENT_CREATION_FAILED;
    }
#ifdef DEBUG
    printf("HyperDex client created.\n\n");
#endif /* DEBUG*/
#ifdef TIMER
    timer.endTime(__FUNCTION__);
#endif
    return OPERATION_SUCCESSFUL;
}

int HyperdexClient::getKey(int64_t operationId, Key &key) {
    auto index = operationToKeyMap.find(operationId);
    if (index == operationToKeyMap.end()) return -1;
    else {
        if (index->second.completionStatus == 1) {
            key.name = index->second.key->name;
            key.size = index->second.key->size;
            key.data = index->second.key->data;
            #ifdef DEBUG
            if(index->second.operationType==1) {
                std::cout << "Put Key: " << key.name << std::endl;
            }else{
                std::cout << "Get Key: " << key.name << std::endl;
            }
            #endif /* DEBUG*/
            return OPERATION_SUCCESSFUL;
        } else {
            enum hyperdex_client_returncode loop_status;
            int found = 0;
            while (found == 0) {
                int64_t loopId = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
                if(loopId==-1){
                    return getKey(operationId,key);
                }
                if (loopId == operationId) {
                    index = operationToKeyMap.find(operationId);
                    if (index->second.operationType == 0) {
                        //GET OPERATION
                        if(index->second.attributes!= nullptr) {
                            index->second.key->data = new char[(*(index->second.attributes))[0].value_sz];
                            memcpy(index->second.key->data, (*(index->second.attributes))[0].value,
                                   (*(index->second.attributes))[0].value_sz);
                            index->second.key->size = (*(index->second.attributes))[0].value_sz;
                        }else{
#ifdef DEBUG
                            std::cout << "Get Failed for Key: " << key.name << std::endl;
#endif
                        }
                    }
#ifdef DEBUG
                    if(index->second.operationType==1) {
                        std::cout << "Put Key: " << key.name << std::endl;
                    }else{
                        std::cout << "Get Key: " << key.name << std::endl;
                    }
#endif
                    key.name = index->second.key->name;
                    key.size = index->second.key->size;
                    key.data = index->second.key->data;
                    index->second.completionStatus = 1;
                    return OPERATION_SUCCESSFUL;
                } else {
                    if (loopId != -1) {
                        index = operationToKeyMap.find(loopId);
                        if (index->second.operationType == 0) {
                            //GET OPERATION
                            index->second.key->data = (void *) &((*(index->second.attributes))[0].value);
                            index->second.key->size = (*(index->second.attributes))[0].value_sz;
                        }
                        index->second.completionStatus = 1;
                        key.name = index->second.key->name;
                        key.size = index->second.key->size;
                        key.data = index->second.key->data;
                    }
                }
            }
        }
    }
    return -1;
}

int HyperdexClient::logRequest(int64_t operationId, const char *OPERATION_TYPE, Key &key,
                               const hyperdex_client_attribute **attributes, size_t *attributes_sz) {
    OperationData data;
    data.completionStatus = 0;
    if (std::strcmp(OPERATION_TYPE, GET_OPERATION)==0) {
        data.operationType = 0;
    } else {
        data.operationType = 1;
    }
    data.attributes = attributes;
    data.attributes_sz = attributes_sz;
    data.key = &key;
    operationToKeyMap.insert(std::make_pair(operationId, data));
    return OPERATION_SUCCESSFUL;
}











