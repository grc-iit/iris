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


int main(int argc, char *args[]) {
  std::cout << "Hello from main" << std::endl;
  /*char * write_buf;
  size_t op_size = 2*MAX_OBJ_SIZE;
  write_buf = randstring(op_size);
  char * read_buf = (char *)malloc(FILE_BUFFER_CAPACITY);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  fh = iris::fopen("file0.dat", "w");
  iris::fwrite(write_buf, 1, 100, fh);
  iris::fread(read_buf, 1, 100, fh);
  iris::fclose(fh);*/

  return 0;
}