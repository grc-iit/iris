//
// Created by anthony on 12/24/16.
//

#include <iostream>
#include <chrono>
#include <sys/time.h>
#include "local_tests.h"
#include "../src/iris.h"
#include "../src/utils/Timer.h"


int local_tests::simple_open_close(int repetitions) {
  std::cout << "Simple Open-Close TEST" <<std::endl;
  FILE* fh;
  Timer timer = Timer(); timer.startTime();
  for(int i =0; i<repetitions; ++i){
    char filename[90];
    sprintf(filename,"/home/anthony/temp_files/file_%d.dat", i);
    fh = iris::fopen(filename, "w");
    if(fh == NULL){
      fprintf(stderr, "File Open failed with null fh");
    }
    iris::fclose(fh);
  }
  timer.endTime("IRIS");



  timer.startTime();
  for(int i =0; i<repetitions; ++i){
    char filename[90];
    sprintf(filename,"/home/anthony/temp_files/file_%d.dat", i);
    fh = std::fopen(filename, "w");
    if(fh == NULL){
      fprintf(stderr, "File Open failed with NULL fh");
    }
    std::fclose(fh);
  }
  timer.endTime("POSIX");

  for(int i =0; i<repetitions; ++i) {
    char filename[90];
    sprintf(filename,"/home/anthony/temp_files/file_%d.dat", i);
    if (remove(filename) != 0) perror("Error deleting file");
  }
  return 0;
}

int local_tests::read_after_write(size_t writeMB, size_t readMB) {
  std::cout << "RAW (Read After Write) TEST\n" <<std::endl;
  size_t op_size;
  writeMB >= readMB ? op_size = writeMB * 1024 * 1024
                    : op_size = readMB * 1024 * 1024;
  char * write_buf = randstring(op_size);
  char *read_buf = (char *) malloc(op_size);

  FILE* fh;
  size_t bytes_read=0;
  size_t bytes_written =0;

//IRIS
  Timer timer = Timer(); timer.startTime();
  fh = iris::fopen("file.dat", "w");
  bytes_written = iris::fwrite(write_buf, sizeof(char), writeMB* 1024 * 1024,
      fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written << std::endl;
  iris::fclose(fh);
  fh = iris::fopen("file.dat", "r");
  bytes_read = iris::fread(read_buf, sizeof(char), readMB *1024 * 1024, fh);
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  iris::fclose(fh);
  timer.endTime("IRIS");

//POSIX
  write_buf = randstring(op_size);
  timer.startTime();
  fh = std::fopen("/home/anthony/file1.dat", "w");
  bytes_written = std::fwrite(write_buf, sizeof(char), writeMB * 1024 * 1024, fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written <<
                                std::endl;
  std::fclose(fh);
  fh = std::fopen("/home/anthony/file1.dat", "r");
  bytes_read = std::fread(read_buf, sizeof(char), readMB * 1024 * 1024, fh);
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  std::fclose(fh);
  timer.endTime("POSIX");

  if(write_buf != nullptr) free(write_buf);
  if(read_buf!= nullptr) free(read_buf);
  return 0;
}
int local_tests::multiple_reads(size_t writeMB, size_t readMB) {
  std::cout << "MR (Multiple Reads) TEST\n" <<std::endl;
  size_t op_size;
  writeMB >= readMB ? op_size = writeMB * 1024*1024
                    : op_size = readMB * 1024*1024;
  char * write_buf = randstring(op_size);
  char *read_buf = (char *) malloc(op_size);

  FILE* fh;
  size_t bytes_read=0;
  size_t bytes_written =0;
//IRIS
  fh = iris::fopen("file.dat", "w");
  bytes_written = iris::fwrite(write_buf, sizeof(char), writeMB*1024*1024, fh);
  /*bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: "<<bytes_written<<std::endl;*/
  iris::fclose(fh);

  fh = iris::fopen("file.dat", "r");
  Timer timer = Timer(); timer.startTime();
  for(size_t i=0; i< writeMB && bytes_read < bytes_written; ++i){
    bytes_read += iris::fread(read_buf, sizeof(char), readMB*1024*1024, fh);
    //iris::fseek(fh, 0, SEEK_SET);
  }
  timer.endTime("IRIS");
  iris::fclose(fh);

  /*bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;*/

//POSIX
  bytes_read =0;
  bytes_written =0;
  fh = std::fopen("/home/anthony/temp/file1.dat", "w");
  bytes_written = std::fwrite(write_buf, sizeof(char), writeMB * 1024*1024, fh);
  /*bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written <<
                                std::endl;*/
  std::fclose(fh);



  fh = std::fopen("/home/anthony/temp/file1.dat", "r");
  timer.startTime();
  for(size_t i=0; i< writeMB && bytes_read < bytes_written; ++i){
    bytes_read += std::fread(read_buf, sizeof(char), readMB*1024*1024,fh);
    //std::fseek(fh, 0, SEEK_SET);
  }
  timer.endTime("POSIX");
  std::fclose(fh);

  if(write_buf != nullptr) free(write_buf);
  if(read_buf!= nullptr) free(read_buf);
  return 0;
}
char *local_tests::randstring(std::size_t length) {
  int n;
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
  char *randomString = NULL;
  if (length) {
    randomString = (char *) malloc(sizeof(char) * (length + 1));
    if (randomString) {
      for (n = 0; n < length; n++) {
        int key = rand() % (int) (sizeof(charset) - 1);
        randomString[n] = charset[key];
      }
      randomString[length] = '\0';
    }
  }
  return randomString;
}


