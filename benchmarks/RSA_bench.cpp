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

// 512-bit密钥生成
static void RSA_512bits_KeyGen(benchmark::State& state) {
    for (auto _ : state){
        GenerateKey(512);
    }
}
BENCHMARK(RSA_512bits_KeyGen);

// 768-bit密钥生成
static void RSA_768bits_KeyGen(benchmark::State& state) {
    for (auto _ : state){
        GenerateKey(768);
    }
}
BENCHMARK(RSA_768bits_KeyGen);
