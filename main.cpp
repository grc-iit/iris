#include <iostream>
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
int basic();
int test3();
int firstTest();
int main(int argc, char *args[]) {

  std::cout << "Main" << std::endl;
  //firstTest();
  //basic();
  test3();
  return 0;
}
int firstTest(){
  FILE* fh;
  fh = iris::fopen("file0.dat", "w");
  iris::fclose(fh);
  return 0;
}
int basic(){
  char * write_buf;

  size_t op_size = 20;
  write_buf = randstring(op_size);
  char * read_buf = (char *)malloc(FILE_BUFFER_CAPACITY);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 1, 20, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 1, 20, fh);
  iris::fclose(fh);

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
  write_buf = "1111111111111111111122222222222222222222";
  char * read_buf = (char *)malloc(op_size);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  fh = iris::fopen("file1.dat", "w");
  iris::fwrite(write_buf, 1, 30, fh);
  iris::fclose(fh);
  fh = iris::fopen("file1.dat", "r");
  iris::fread(read_buf, 1, 30, fh);
  return 0;
}