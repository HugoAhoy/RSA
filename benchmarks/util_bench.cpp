#include "benchmark/benchmark.h"
#include "util.hpp"

// 随机生成n位大整数
static void util_Random_nbits(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Int(2048);
    }
}
BENCHMARK(util_Random_nbits);

// 随机生成n位大素数数
static void util_Random_nbits_prime(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Prime(384);
    }
}
BENCHMARK(util_Random_nbits_prime);