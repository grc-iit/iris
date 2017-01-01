//
// Created by anthony on 12/16/16.
//

#ifndef IRIS_RETURN_CODES_H
#define IRIS_RETURN_CODES_H

typedef enum iris_return_codes{
  OPERATION_SUCCESSFUL               = 7777,

  /* Error codes*/
  METADATA_CREATION_FAILED           = 7800,
  FP_DOES_NOT_EXIST                  = 7801,
  FILENAME_DOES_NOT_EXIST            = 7802,
  METADATA_UPDATE_FAILED__OPEN       = 7803,
  METADATA_UPDATE_FAILED__CLOSE      = 7804,
  METADATA_UPDATE_FAILED__READ       = 7805,
  METADATA_UPDATE_FAILED__WRITE      = 7806,
  UPDATE_FILE_POINTER_FAILED         = 7807,
  PREFETCH_ENGINE_FAILED             = 7808,
  FETCH_FAILED                       = 7809,
  FH_DOES_NOT_EXIST                  = 7810,

  FLUSH_SORTEDTABLES                 = 7820,

  HYPERDEX_ADMIN_CREATION_FAILED     = 7900,
  HYPERDEX_CLIENT_CREATION_FAILED    = 7901,
  HYPERDEX_GET_OPERATION_FAILED      = 7902,
  HYPERDEX_PUT_OPERATION_FAILED      = 7903,
  NO_DATA_FOUND                      = 7950

} iris_returncode;


#endif //IRIS_RETURN_CODES_H
