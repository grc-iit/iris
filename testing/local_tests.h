/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
 * <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of Iris
 * 
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
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
  static int s3test(size_t amount);

private:
  static char *randstring(std::size_t length);
};

#endif //IRIS_LOCAL_TESTS_H
