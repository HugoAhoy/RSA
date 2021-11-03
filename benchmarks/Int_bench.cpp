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

// 大数除法
static void Int_div(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(2048);
        b = Random_Nbits_Int(1024);
        state.ResumeTiming();
        a/b;
    }
}
BENCHMARK(Int_div);


static void Int_div_bs(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(2048);
        b = Random_Nbits_Int(1024);
        state.ResumeTiming();
        Int::div_by_binary_search(a,b);
    }
}
BENCHMARK(Int_div_bs);

static void Int_mod(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(2048);
        b = Random_Nbits_Int(1024);
        state.ResumeTiming();
        a%b;
    }
}
BENCHMARK(Int_mod);

static void Int_power(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(1000);
        b = Random_Nbits_Int(500);
        state.ResumeTiming();
        a.power(b-1, b);
    }
}
BENCHMARK(Int_power);

// Karatsuba 大数乘法
static void Int_Karatsuba_mul(benchmark::State& state) {
    Int a, b, res;
    for (auto _ : state){
        state.PauseTiming();
        a = Random_Nbits_Int(1024);
        b = Random_Nbits_Int(1024);
        state.ResumeTiming();
        a.Karatsuba_mul(b);
    }
}
BENCHMARK(Int_Karatsuba_mul);
