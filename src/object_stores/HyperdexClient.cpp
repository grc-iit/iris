//
// Created by anthony on 12/10/16.
//

#include "HyperdexClient.h"
#include "../utils/Buffer.h"
#include <hyperdex/client.h>
#include <hyperdex/admin.h>

/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<HyperdexClient> HyperdexClient::instance = nullptr;

HyperdexClient::HyperdexClient() {
  if(init() != OPERATION_SUCCESSUL){
    //TODO: throw exception here!
  }
}

HyperdexClient::~HyperdexClient() {}


std::shared_ptr<HyperdexClient> HyperdexClient::getInstance() {
  if (instance == nullptr) {
    instance = std::shared_ptr<HyperdexClient>(new HyperdexClient());
  }
  return instance;
}

int HyperdexClient::get(Key &key) {
  int64_t op_id=0, loop_id=0;
  const struct hyperdex_client_attribute* attributes = 0;
  std::size_t attributes_sz = 0;
  enum hyperdex_client_returncode op_status2, loop_status2;
  op_id = hyperdex_client_get(hyperdexClient,
                              SPACE,
                              key.name,
                              sizeof(key.name),
                              &op_status2,
                              &attributes,
                              &attributes_sz);
  loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status2);
  if (op_id == loop_id && loop_status2 == HYPERDEX_CLIENT_SUCCESS && attributes_sz!=0){
    //key.data = (void*) attributes[0].value;
    key.data=malloc(attributes[0].value_sz);
    memcpy(key.data,attributes[0].value,attributes[0].value_sz);
    key.size = attributes[0].value_sz;
  }else{
    return HYPERDEX_GET_OPERATION_FAILED;
  }
#ifdef DEBUG
  std::printf("Getting Data \nkey Name : %s key Data %-30s \n", key.name,key.data );
#endif

    hyperdex_client_destroy_attrs(attributes,attributes_sz);
  return OPERATION_SUCCESSUL;
}

int HyperdexClient::put(Key &key) {
  int status;
  struct hyperdex_client_attribute attribute;
  enum hyperdex_client_returncode op_status, loop_status;
  int64_t op_id=0, loop_id=0;

  Key originalKey=key;
  Buffer dataBuffer;
#ifdef DEBUG
    std::printf("Before Put Data \nkey Name : %s key Data %-30s \n", key.name,key.data );
#endif

  if(key.offset==0){
    if(key.size!=MAX_OBJ_SIZE){
      status=get(key);
      if(status==OPERATION_SUCCESSUL && key.size > originalKey.size){
        dataBuffer=Buffer(key.data,key.size);
        dataBuffer.assign(originalKey.data,originalKey.size);
        key.data=dataBuffer.data();
      }
    }
  }else{
    status=get(key);
    if(status==OPERATION_SUCCESSUL) {
      if (key.size > originalKey.offset + originalKey.size) {
        std::memcpy((char*)key.data + originalKey.offset, originalKey.data,
                    originalKey.size);
      } else{
        dataBuffer=Buffer(key.data,originalKey.offset);
        dataBuffer.append(originalKey.data);
        key.data=dataBuffer.data();
      }
    }
  }
    std::size_t attributes_sz = 1;
  attribute.attr =ATTRIBUTE_NAME;
  attribute.value = (const char *) key.data;
  attribute.value_sz = key.size;
  attribute.datatype=HYPERDATATYPE_STRING;
  op_id = hyperdex_client_put(hyperdexClient,
                              SPACE,
                              key.name,
                              sizeof(key.name),
                              &attribute,
                              attributes_sz,
                              &op_status);
    loop_id = hyperdex_client_loop(hyperdexClient, -1, &loop_status);
  if (loop_id != op_id || loop_status != HYPERDEX_CLIENT_SUCCESS) {
#ifdef DEBUG
    std::cout<< HYPERDEX_PUT_OPERATION_FAILED << " Hyperdex put status " << loop_status << std::endl;
#endif
    return HYPERDEX_PUT_OPERATION_FAILED;
  }
#ifdef DEBUG
    std::printf("after Put  Data \nkey Name : %s key Data %-30s \n", key.name,key.data );
#endif
      return OPERATION_SUCCESSUL;
}


int HyperdexClient::remove(Key &key) {
  return OPERATION_SUCCESSUL;
}

int HyperdexClient::init() {
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
  } else {
    printf("Success creating space:{ %s }\n", SPACE);
  }

  /* Checking cluster stability*/
  admin_id = hyperdex_admin_wait_until_stable(admin, &admin_status);
  loop_id = hyperdex_admin_loop(admin, -1, &loop_status);
  if (loop_id != admin_id || admin_status != HYPERDEX_ADMIN_SUCCESS)
    printf("Admin ID: %ld Status: %d \n",admin_id, admin_status);
  else printf("Cluster stable\n");
  hyperdex_admin_destroy(admin);

  /* Setup the hyperdex client */
  hyperdexClient = hyperdex_client_create(COORDINATOR, COORDINATOR_PORT);
  /* make sure the client is OK */
  if (!hyperdexClient) {
    fprintf(stderr,"Cannot create HyperDex client.\n");
    return HYPERDEX_CLIENT_CREATION_FAILED;
  }
  else printf("HyperDex client created.\n\n");
  return OPERATION_SUCCESSUL;
}








