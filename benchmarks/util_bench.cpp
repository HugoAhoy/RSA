#include "benchmark/benchmark.h"
#include "util.hpp"

// 随机生成n位大整数
static void util_Random_nbits(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Int(2048);
    }
}
BENCHMARK(util_Random_nbits);
