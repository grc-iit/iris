#include <cstdio>
#include "testing/local_tests.h"


int main(int argc, char *args[]) {
  //freopen("/home/admin2/log.csv", "a+", stdout);
  //local_tests::simple_open_close(100);
  int status = local_tests::read_after_write(20,20);
  //if(status !=0) return -1;
  //local_tests::multiple_reads(26, 2);
  return 0;
}

