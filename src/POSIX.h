/*******************************************************************************
* File POSIX.h
*
* Goal: This is the POSIX interface
*
* Created: December 10th, 2016  - Anthony Kougkas
 * Updated:
* Illinois Institute of Technology - SCS Lab
* (C) 2016
******************************************************************************/
#ifndef IRIS_POSIX_H
#define IRIS_POSIX_H
/******************************************************************************
*include files
******************************************************************************/
#include <cstdio>
#include "API.h"
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
