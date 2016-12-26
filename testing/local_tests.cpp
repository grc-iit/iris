//
// Created by anthony on 12/24/16.
//

#include <iostream>
#include <chrono>
#include "local_tests.h"
#include "../src/iris.h"

int local_tests::simple_open_close(int repetitions) {
  std::cout << "Simple Open-Close TEST" <<std::endl;
  FILE* fh;
  auto t1 = std::chrono::high_resolution_clock::now();
  for(int i =0; i<repetitions; ++i){
    char filename[90];
    sprintf(filename,"/home/anthony/temp_files/file_%d.dat", i);
    fh = iris::fopen(filename, "w");
    if(fh == NULL){
      fprintf(stderr, "File Open failed with null fh");
    }
    iris::fclose(fh);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "IRIS() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";



  t1 = std::chrono::high_resolution_clock::now();
  for(int i =0; i<repetitions; ++i){
    char filename[90];
    sprintf(filename,"/home/anthony/temp_files/file_%d.dat", i);
    fh = std::fopen(filename, "w");
    if(fh == NULL){
      fprintf(stderr, "File Open failed with NULL fh");
    }
    std::fclose(fh);
  }
  t2 = std::chrono::high_resolution_clock::now();
  std::cout << "POSIX() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";

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
  auto t1 = std::chrono::high_resolution_clock::now();
  fh = iris::fopen("/home/anthony/temp/file1.dat", "w");
  bytes_written = iris::fwrite(write_buf, writeMB,  1024 * 1024, fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written << std::endl;
  iris::fclose(fh);
  fh = iris::fopen("/home/anthony/temp/file1.dat", "r");
  bytes_read = iris::fread(read_buf, readMB, 1024 * 1024, fh);
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  iris::fclose(fh);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "IRIS() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";

//POSIX
  t1 = std::chrono::high_resolution_clock::now();
  fh = std::fopen("/home/anthony/temp/file1.dat", "w");
  bytes_written = std::fwrite(write_buf, sizeof(char), writeMB * 1024 * 1024, fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written <<
                                std::endl;
  std::fclose(fh);
  fh = std::fopen("/home/anthony/temp/file1.dat", "r");
  bytes_read = std::fread(read_buf, sizeof(char), readMB * 1024 * 1024, fh);
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  std::fclose(fh);
  t2 = std::chrono::high_resolution_clock::now();
  std::cout << "POSIX() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";

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
//POSIX

  fh = std::fopen("/home/anthony/temp/file1.dat", "w");
  bytes_written = std::fwrite(write_buf, sizeof(char), writeMB * 1024*1024, fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: " << bytes_written <<
                                std::endl;
  std::fclose(fh);


  auto t1 = std::chrono::high_resolution_clock::now();
  fh = std::fopen("/home/anthony/temp/file1.dat", "r");
  for(size_t i=0; i< writeMB; ++i){
    bytes_read += std::fread(read_buf, sizeof(char), readMB*1024*1024,fh);
    //std::fseek(fh, 0, SEEK_SET);
  }
  std::fclose(fh);
  auto t2 = std::chrono::high_resolution_clock::now();
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  std::cout << "POSIX() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";
//IRIS
  bytes_read =0;
  bytes_written =0;
  fh = iris::fopen("file.dat", "w");
  bytes_written = iris::fwrite(write_buf, sizeof(char), writeMB*1024*1024, fh);
  bytes_written == 0 ? std::cout <<"File write failed!" <<std::endl
                     : std::cout<<"Bytes written: "<<bytes_written<<std::endl;
  iris::fclose(fh);
  t1 = std::chrono::high_resolution_clock::now();
  fh = iris::fopen("file.dat", "r");

  for(size_t i=0; i< writeMB; ++i){
    bytes_read += iris::fread(read_buf, sizeof(char), readMB*1024*1024, fh);
    //iris::fseek(fh, 0, SEEK_SET);
  }
  iris::fclose(fh);
  t2 = std::chrono::high_resolution_clock::now();
  bytes_read == 0 ? std::cout <<"File read failed!" <<std::endl
                  : std::cout<<"Bytes read: " << bytes_read << std::endl;
  std::cout << "IRIS() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n\n";


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


