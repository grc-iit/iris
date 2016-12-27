#include "testing/local_tests.h"


int main(int argc, char *args[]) {
  //local_tests::simple_open_close(10000);
  //int status = local_tests::read_after_write(2000,2000);
  //if(status !=0) return -1;
  local_tests::multiple_reads(20, 1);
  return 0;
}

