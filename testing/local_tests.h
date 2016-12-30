//
// Created by anthony on 12/24/16.
//

#ifndef IRIS_LOCAL_TESTS_H
#define IRIS_LOCAL_TESTS_H

#include <cstring>

class local_tests {
public:
  static int simple_open_close(int repetitions);
  static int read_after_write(size_t writeMB, size_t readMB);
  static int multiple_reads(size_t writeMB, size_t readMB);
  static int alternateReadandWrite(size_t amount, int count);
    static int s3test();
  //int random_writes();

  //int random_reads();
private:
  static char *randstring(std::size_t length);
};

#endif //IRIS_LOCAL_TESTS_H
