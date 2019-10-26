/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
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


  HYPERDEX_ADMIN_CREATION_FAILED     = 7900,
  HYPERDEX_CLIENT_CREATION_FAILED    = 7901,
  HYPERDEX_GET_OPERATION_FAILED      = 7902,
  HYPERDEX_PUT_OPERATION_FAILED      = 7903,
  NO_DATA_FOUND                      = 7950

} iris_returncode;


#endif //IRIS_RETURN_CODES_H
