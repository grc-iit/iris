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
// Created by anthony on 12/28/16.
//

#include <iostream>
#include <iomanip>
#include "Timer.h"

void Timer::startTime() {
  t1 = std::chrono::high_resolution_clock::now();
}

void Timer::endTime(std::string fnName) {
  auto t2 = std::chrono::high_resolution_clock::now();
  auto t =  std::chrono::duration_cast<std::chrono::nanoseconds>(
      t2 - t1).count()/1000000.0;
  if( t > 0.001){
    std::cout << fnName << "() "
              << std::setprecision(6) << t
              << " ms\n";
  }

}
