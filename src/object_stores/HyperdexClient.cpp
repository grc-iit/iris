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
  cacheManager=CacheManager::getInstance();
  prefetcherFactory = PrefetcherFactory::getInstance();
  if(init() != OPERATION_SUCCESSFUL){
    fprintf(stderr,"Hyperdex failed to start! Please check the configuration of"
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
  int64_t op_id=0, loop_id=0;
  const struct hyperdex_client_attribute* attributes = 0;
  std::size_t attributes_sz = 0;
  enum hyperdex_client_returncode op_status, loop_status;
  op_id = hyperdex_client_get(hyperdexClient,
                              SPACE,
                              key.name,
                              strlen(key.name),
                              &op_status,
                              &attributes,
                              &attributes_sz);
  loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
  if (op_id == loop_id && loop_status == HYPERDEX_CLIENT_SUCCESS && attributes_sz!=0){
    key.data=malloc(attributes[0].value_sz);
    memcpy(key.data, attributes[0].value, attributes[0].value_sz);
    key.size = attributes[0].value_sz;
  }else{
#ifdef DEBUG
    fprintf(stderr, "Get FAILED! \nOP ID: %ld, STAT: %d, LOOP ID: %ld, STAT:"
        " %d\n", op_id, op_status, loop_id, loop_status);
#endif /* DEBUG*/
    return HYPERDEX_GET_OPERATION_FAILED;
  }
#ifdef DEBUG
  std::cout << "Get operation complete" << std::endl;
  std::cout << "Key: " << key.name << std::endl;
#endif /* DEBUG*/
  hyperdex_client_destroy_attrs(attributes,attributes_sz);
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
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

  if(key.offset == 0){
    if(key.size != MAX_OBJ_SIZE){
      status = get(key);
      if(status == OPERATION_SUCCESSFUL && key.size > originalKey.size){
        dataBuffer = Buffer(key.data,key.size);
        dataBuffer.assign(originalKey.data, originalKey.size);
        key.data = dataBuffer.data();
      }
    }
  }else{
    status = get(key);
    if(status == OPERATION_SUCCESSFUL) {
      if (key.size > originalKey.offset + originalKey.size){
        std::memcpy((char*)key.data + originalKey.offset, originalKey.data,
                    originalKey.size);
      } else{
        dataBuffer = Buffer(key.data, originalKey.offset);
        dataBuffer.append(originalKey.data);
        key.data = dataBuffer.data();
      }
    }
  }
  /*Prepare parameters for th actual put call on Hyperdex*/
  std::size_t attribute_sz = 1;
  attribute.attr =ATTRIBUTE_NAME;
  attribute.datatype=HYPERDATATYPE_STRING;
  attribute.value = (const char *) key.data;
  attribute.value_sz = key.size;

  op_id = hyperdex_client_put(hyperdexClient,
                              SPACE,
                              key.name,
                              strlen(key.name),
                              &attribute,
                              attribute_sz,
                              &op_status);
  loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
  if (loop_id != op_id || loop_status != HYPERDEX_CLIENT_SUCCESS) {
#ifdef DEBUG
    fprintf(stderr, "PUT FAILED! \nOP ID: %ld, STAT: %d, LOOP ID: %ld, STAT:"
        " %d\n", op_id, op_status, loop_id, loop_status);
#endif /* DEBUG*/
    return HYPERDEX_PUT_OPERATION_FAILED;
  }
#ifdef DEBUG
  std::cout << "Put operation complete" << std::endl;
  std::cout << "Key: " << key.name << std::endl;
#endif /* DEBUG*/
#ifdef TIMER
  timer.endTime(__FUNCTION__);
#endif
  return OPERATION_SUCCESSFUL;
}

int HyperdexClient::getRange(std::vector<Key> &keys) {
#ifdef TIMER
  Timer timer = Timer(); timer.startTime();
#endif
  auto objectStorePrefetcher = std::static_pointer_cast<ObjectStorePrefetcher>
      (prefetcherFactory->getPrefetcher(OBJECTSTORE_PREFETCHER));

  int64_t op_id[keys.size()], loop_id;
  const struct hyperdex_client_attribute* attributes[keys.size()];
  std::size_t attributes_sz[keys.size()];
  enum hyperdex_client_returncode op_status[keys.size()], loop_status;
  //std::vector<bool> loopCounter(keys.size(), false);
  //std::future<int> asyncFetch;
  for(int i=0; i< keys.size(); ++i) {
    if (cacheManager->isCached(keys[i]) != OPERATION_SUCCESSFUL) {
      if(i+1 < keys.size())
        /*asyncFetch = std::async(std::launch::async,
                                 &ObjectStorePrefetcher::fetchKey,
                                objectStorePrefetcher, keys[i+1]);*/
      op_id[i] = hyperdex_client_get(hyperdexClient,
                                     SPACE,
                                     keys[i].name,
                                     strlen(keys[i].name),
                                     &op_status[i],
                                     &attributes[i],
                                     &attributes_sz[i]);
      //loopCounter[i] = true;
      //if(i+1 < keys.size()) asyncFetch.get();
    }
  }
  int counter1 = 0, counter2 =0;
  while(counter1 < keys.size()) {
    long int index = -1;
    loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
    for (int i = 0; i < keys.size(); ++i) {
      if (op_id[i] == loop_id) {
        index = i;
        break;
      }
    }
    if (index != -1) {
      if (loop_status == HYPERDEX_CLIENT_SUCCESS) {
        keys[index].data = malloc(attributes[index][0].value_sz);
        memcpy(keys[index].data, attributes[index][0].value,
               attributes[index][0]
                   .value_sz);
        counter2++;
#ifdef DEBUG
        std::cout << "Get operation complete" << std::endl;
        std::cout << "Key: " << keys[index].name << std::endl;
#endif /* DEBUG*/
      } else {
#ifdef DEBUG
        fprintf(stderr, "GET failed for Index: %ld", index);
#endif /* DEBUG*/
      }
      counter1++;
      hyperdex_client_destroy_attrs(attributes[index], attributes_sz[index]);
    }
  }
  if (counter1 != counter2) {
#ifdef DEBUG
    fprintf(stderr, "GET FAILED! ");
#endif /* DEBUG*/
    return HYPERDEX_GET_OPERATION_FAILED;
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

  for(int i=0; i<keys.size(); ++i) {
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
  }
  int counter1 = 0, counter2 =0;
  while(counter1 < keys.size()){
    loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
    if(loop_status == HYPERDEX_CLIENT_SUCCESS){
      counter2++;
    }
    else{
      auto index =  loop_id -1;
#ifdef DEBUG
      fprintf(stderr, "PUT failed for Index: %ld", index);
#endif /* DEBUG*/
    }
    counter1++;
  }
  if(counter1 != counter2){
#ifdef DEBUG
    fprintf(stderr, "PUT FAILED! ");
#endif /* DEBUG*/
    return HYPERDEX_PUT_OPERATION_FAILED;
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
  struct hyperdex_admin * admin =
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
    fprintf(stderr,"Failed to remove old spaces!\n"
                "ADMIN ID: %ld, STAT: %d, LOOP ID: %ld, STAT: %d\n",
            admin_id, admin_status, loop_id, loop_status);
  }

  /* add a space */
  admin_id = hyperdex_admin_add_space(admin, DESCRIPTION, &admin_status);
  loop_id = hyperdex_admin_loop(admin, -1, &loop_status);
  if (loop_id != admin_id || admin_status != HYPERDEX_ADMIN_SUCCESS) {
    fprintf(stderr,"Failed to create space!\n"
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
    fprintf(stderr,"Cluster not ready! Admin ID: %ld Status: %d \n",admin_id,
            admin_status);
#ifdef DEBUG
  printf("Cluster stable\n");
#endif /* DEBUG*/
  hyperdex_admin_destroy(admin);

  /* Setup the hyperdex client */
  hyperdexClient = hyperdex_client_create(COORDINATOR, COORDINATOR_PORT);
  /* make sure the client is OK */
  if (!hyperdexClient) {
    fprintf(stderr,"Cannot create HyperDex client.\n");
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











