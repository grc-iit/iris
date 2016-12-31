#include <cstdio>
#include "testing/local_tests.h"


int main(int argc, char *args[]) {
  //freopen("/home/anthony/log.csv", "a+", stdout);
  local_tests::simple_open_close(100);
  local_tests::read_after_write(5,5);
  local_tests::multiple_reads(5, 1);
  local_tests::alternateReadandWrite(1,5);
  local_tests::s3test(100);
  return 0;
}

