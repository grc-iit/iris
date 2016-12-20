//
// Created by anthony on 12/16/16.
//

#ifndef IRIS_RETURN_CODES_H
#define IRIS_RETURN_CODES_H

typedef enum iris_returncode{
  OPERATION_SUCCESSUL                = 7777,

  /* Error codes*/
  METADATA_CREATION_FAILED           = 7800,
  ON_OPEN_METADATA_UPDATE_FAILED     = 7801,
  ON_CLOSE_METADATA_UPDATE_FAILED    = 7802,
  UPDATE_FILE_POINTER_FAILED         = 7803,
  FP_NOT_EXIST                       = 7804,

};


#endif //IRIS_RETURN_CODES_H