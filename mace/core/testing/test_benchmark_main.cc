//
// Copyright (c) 2017 XiaoMi All rights reserved.
//

#include <iostream>

#include "gflags/gflags.h"
#include "mace/core/testing/test_benchmark.h"
#include "mace/public/mace.h"

DEFINE_string(pattern, "all", "op benchmark pattern, eg:.*CONV.*");
DEFINE_int32(gpu_perf_hint, 3, "0:DEFAULT/1:LOW/2:NORMAL/3:HIGH");
DEFINE_int32(gpu_priority_hint, 3, "0:DEFAULT/1:LOW/2:NORMAL/3:HIGH");
DEFINE_int32(omp_num_threads, 1, "num of openmp threads");
DEFINE_int32(cpu_power_option, 1,
             "0:DEFAULT/1:HIGH_PERFORMANCE/2:BATTERY_SAVE");

int main(int argc, char **argv) {
  gflags::SetUsageMessage("some usage message");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  // config runtime
  mace::ConfigOpenCLRuntime(
      static_cast<mace::GPUPerfHint>(FLAGS_gpu_perf_hint),
      static_cast<mace::GPUPriorityHint>(FLAGS_gpu_priority_hint));
  mace::ConfigOmpThreadsAndAffinity(
      FLAGS_omp_num_threads,
      static_cast<mace::CPUPowerOption>(FLAGS_cpu_power_option));

  mace::testing::Benchmark::Run(FLAGS_pattern.c_str());
  return 0;
}
