//
// Created by anthony on 12/10/16.
//

#ifndef IRIS_POSIX_H
#define IRIS_POSIX_H

#include <cstdio>
#include "API.h"
#include "utils/ObjectStorePrefetcher.h"

/******************************************************************************
*Interface operations
******************************************************************************/
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int fseek(FILE *stream, long int offset, int origin);
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
int fileno(FILE *stream);



#endif //IRIS_POSIX_H
