
#include "testing/local_tests.h"


int main(int argc, char *args[]) {
  //local_tests::simple_open_close(10000);
  //local_tests::read_after_write(100,100);
  local_tests::multiple_reads(2000, 1); //bug for input 20,2 and 50,2048
  return 0;
}

