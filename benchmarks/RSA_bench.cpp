#include "benchmark/benchmark.h"
#include "RSA.hpp"

// 128-bit密钥生成
// static void RSA_128bits_KeyGen(benchmark::State& state) {
//     for (auto _ : state){
//         GenerateKey(128);
//     }
// }
// BENCHMARK(RSA_128bits_KeyGen);

// 256-bit密钥生成
static void RSA_256bits_KeyGen(benchmark::State& state) {
    for (auto _ : state){
        GenerateKey(256);
    }
}
BENCHMARK(RSA_256bits_KeyGen);
