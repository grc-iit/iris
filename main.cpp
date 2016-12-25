
#include "testing/local_tests.h"


int main(int argc, char *args[]) {
  //local_tests::simple_open_close(10000);
  //local_tests::read_after_write(10,10);
  local_tests::multiple_reads(50,1);
  return 0;
}

