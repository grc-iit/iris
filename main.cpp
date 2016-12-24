#include <iostream>
#include <chrono>
#include "src/iris.h"

char *randstring(size_t length) {
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
int test2();

int read_after_write();
int test3();
int firstTest();

int write_copy_read();
int main(int argc, char *args[]) {

  std::cout << "Main" << std::endl;
  //firstTest();
  //read_after_write();
  write_copy_read();
  //test3();
  return 0;
}
int firstTest(){
  FILE* fh;
  fh = iris::fopen("file0.dat", "w");
  iris::fclose(fh);
  return 0;
}

int read_after_write() {
  char * write_buf;

  size_t op_size = 20 * 1024 * 1024;//20971520
  write_buf = randstring(op_size);
  char *writebuf1 = (char *) "1";
  char *read_buf = (char *) malloc(op_size);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  auto t1 = std::chrono::high_resolution_clock::now();
  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 20, 1024 * 1024, fh);
  //iris::fseek(fh, 5242880, SEEK_SET);
  //iris::fwrite(write_buf, 10485760, 1, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 20, 1024 * 1024, fh);
  iris::fclose(fh);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "IRIS() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n";


  t1 = std::chrono::high_resolution_clock::now();
  fh = std::fopen("/home/anthony/temp/file1.dat", "w");
  std::fwrite(write_buf, 20, 1024 * 1024, fh);
  //std::fseek(fh, 5242880, SEEK_SET);
  //std::fwrite(write_buf, 10485760, 1, fh);
  std::fclose(fh);
  fh = std::fopen("/home/anthony/temp/file1.dat", "r");
  std::fread(read_buf, 20, 1024 * 1024, fh);
  std::fclose(fh);
  t2 = std::chrono::high_resolution_clock::now();
  std::cout << "POSIX() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n";
  return 0;
}

int write_copy_read() {
  char *write_buf;

  size_t op_size = 1000 * 1024 * 1024;//20971520
  write_buf = randstring(op_size);
  char *writebuf1 = (char *) "1";
  char *read_buf = (char *) malloc(op_size);
  size_t bytes_read = 0;
  size_t bytes_written = 0;

  FILE *fh;
  auto t1 = std::chrono::high_resolution_clock::now();
  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 1000, 1024 * 1024, fh);
  //iris::fseek(fh, 5242880, SEEK_SET);
  //iris::fwrite(write_buf, 10485760, 1, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 1000, 1024 * 1024, fh);
  iris::fclose(fh);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "IRIS() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n";


  t1 = std::chrono::high_resolution_clock::now();
  fh = std::fopen("/home/anthony/temp/file1.dat", "w");
  std::fwrite(write_buf, 1000, 1024 * 1024, fh);
  //std::fseek(fh, 5242880, SEEK_SET);
  //std::fwrite(write_buf, 10485760, 1, fh);
  std::fclose(fh);
  fh = std::fopen("/home/anthony/temp/file1.dat", "r");
  std::fread(read_buf, 1000, 1024 * 1024, fh);
  std::fclose(fh);
  t2 = std::chrono::high_resolution_clock::now();
  std::cout << "POSIX() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                t2 - t1).count()
            << " milliseconds\n";
  return 0;
}

int test2(){
  char * write_buf;

  size_t op_size = 50;
  write_buf = "1111111111111111111122222222222222222222";
  char * read_buf = (char *)malloc(op_size);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;

  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 1, 25, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 1, 20, fh);
  iris::fclose(fh);

  return 0;
}
int test3(){
  char * write_buf;

  size_t op_size = 50;
  write_buf = "1111111111111111111122222222222222222222333333333333333333333333333333";
  char * read_buf = (char *)malloc(op_size);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 1, 50, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 1, 35, fh);
  return 0;
}