#include "benchmark/benchmark.h"
#include "Int.hpp"
#include "util.hpp"

// 大数乘法
static void Int_mul(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(1024);
        b = Random_Nbits_Int(1024);
        state.ResumeTiming();
        a*b;
    }
}
BENCHMARK(Int_mul);
