#include "HyperdexClient.h"
#include "../utils/Buffer.h"
#include <hyperdex/client.h>
#include <hyperdex/admin.h>
/******************************************************************************
*Initialization of static
******************************************************************************/
std::shared_ptr<HyperdexClient> HyperdexClient::instance = nullptr;
/******************************************************************************
*Constructors
******************************************************************************/
HyperdexClient::HyperdexClient() {
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
  return OPERATION_SUCCESSFUL;
}

int HyperdexClient::getRange(std::vector<Key> keys) {
  int64_t op_id[keys.size()], loop_id[keys.size()];
  const struct hyperdex_client_attribute* attributes[keys.size()];
  std::size_t attributes_sz[keys.size()];
  enum hyperdex_client_returncode op_status[keys.size()], loop_status[keys.size()];

  for(int i=0; i< keys.size(); ++i){
    op_id[i] = hyperdex_client_get(hyperdexClient,
                                SPACE,
                                keys[i].name,
                                strlen(keys[i].name),
                                &op_status[i],
                                &attributes[i],
                                &attributes_sz[i]);
  }

  for(int i=0; i< keys.size(); ++i){
    loop_id[i] = hyperdex_client_loop(hyperdexClient, -1, &loop_status[i]);
    if (op_id[i] == loop_id[i] && loop_status[i] == HYPERDEX_CLIENT_SUCCESS &&
        attributes_sz[i]!=0){
      keys[i].data=malloc(attributes[i][0].value_sz);
      memcpy(keys[i].data, attributes[i][0].value, attributes[i][0].value_sz);
      keys[i].size = attributes[i][0].value_sz;
    }else{
#ifdef DEBUG
      fprintf(stderr, "Get FAILED! \nOP ID: %ld, STAT: %d, LOOP ID: %ld, STAT:"
        " %d\n", op_id[i], op_status[i], loop_id[i], loop_status[i]);
#endif /* DEBUG*/
      return HYPERDEX_GET_OPERATION_FAILED;
    }
#ifdef DEBUG
    std::cout << "Get operation complete" << std::endl;
  std::cout << "Key: " << keys[i].name << std::endl;
#endif /* DEBUG*/
    hyperdex_client_destroy_attrs(attributes[i],attributes_sz[i]);
  }
  return OPERATION_SUCCESSFUL;
}

int HyperdexClient::put(Key &key) {
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
  return OPERATION_SUCCESSFUL;
}

int HyperdexClient::remove(Key &key) {
  return OPERATION_SUCCESSFUL;
}
/******************************************************************************
*Init function
******************************************************************************/
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
  return OPERATION_SUCCESSFUL;
}










