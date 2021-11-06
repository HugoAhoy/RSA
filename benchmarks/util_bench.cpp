#include "benchmark/benchmark.h"
#include "util.hpp"

// 随机生成n位大整数
static void util_Random_nbits(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Int(2048);
    }
}
BENCHMARK(util_Random_nbits);

// 随机生成384位大素数数
static void util_Random_nbits_prime_384(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Prime(384);
    }
}
BENCHMARK(util_Random_nbits_prime_384);

// 随机生成128位大素数数
static void util_Random_nbits_prime_128(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Prime(128);
    }
}
BENCHMARK(util_Random_nbits_prime_128);

// 随机生成256位大素数数
static void util_Random_nbits_prime_256(benchmark::State& state) {
    for (auto _ : state){
        Random_Nbits_Prime(256);
    }
}
BENCHMARK(util_Random_nbits_prime_256);