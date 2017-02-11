/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2017 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/clock.h"

#include <sys/time.h>
#include <time.h>

namespace xe {

uint64_t Clock::host_tick_frequency() {
  timespec res;
  clock_getres(CLOCK_MONOTONIC_RAW, &res);

  return uint64_t(res.tv_sec) + uint64_t(res.tv_nsec) * 1000000000ull;
}

uint64_t Clock::QueryHostTickCount() {
  timespec res;
  clock_gettime(CLOCK_MONOTONIC_RAW, &res);

  return uint64_t(res.tv_sec) + uint64_t(res.tv_nsec) * 1000000000ull;
}

uint64_t Clock::QueryHostSystemTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  uint64_t ret = tv.tv_usec;
  ret /= 1000;  // usec -> msec

  ret += (tv.tv_sec * 1000);  // sec -> msec
  return ret;
}

uint32_t Clock::QueryHostUptimeMillis() {
  return uint32_t(QueryHostTickCount() / (host_tick_frequency() / 1000));
}

}  // namespace xe