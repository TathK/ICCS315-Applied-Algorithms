#include <iostream>
#include "fc/btree.h"
#include <benchmark/benchmark.h>
#include <numeric>
#include <random>


#include <mach/mach.h>

inline static size_t GetMemRam() {
    struct task_basic_info info;
    mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size) == KERN_SUCCESS) {
        return double(info.resident_size) / 1024; // KB
    }
    return -1;
}

inline static size_t GetMemPagefile() {
    struct task_basic_info info;
    mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size) == KERN_SUCCESS) {
        return double(info.virtual_size) / 1024; // KB
    }
    return -1;
}


void do_alot_insert(std::vector<int> vec) {
    namespace fc = frozenca;
    fc::BTreeSet<int,1<<3> btree;
    for (int i = 1; i <= 1e6; i++)
        btree.insert(vec[i]);
}

template <int B>

static void BM_StringCreation(benchmark::State& state) {
    using namespace frozenca;
    BTreeSet<int,B>btree{};
    std::vector<int> vec(state.range(0));
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937());

    double before_mem = double(GetMemRam());
    double before_pate_file = double(GetMemPagefile());
    for (auto _ : state)
        for (auto k: vec)
             benchmark::DoNotOptimize(btree.insert(k));
    state.counters["RAM"] = double(GetMemRam()) - before_mem;
    state.counters["Pagefile"] =  double(GetMemPagefile()) - before_pate_file;
}

static void Ideal_B_insert(benchmark::State& state) {
    using namespace frozenca;
    BTreeSet<int,60>btree{};
    std::vector<int> vec(state.range(0));
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937());

    double before_mem = double(GetMemRam());
    double before_pate_file = double(GetMemPagefile());
    for (auto _ : state)
        for (auto k: vec)
             benchmark::DoNotOptimize(btree.insert(k));
    state.counters["RAM"] = double(GetMemRam()) - before_mem;
    state.counters["Pagefile"] =  double(GetMemPagefile()) - before_pate_file;
}
static void set_insert(benchmark::State& state) {

    std::set<int> btree;
    std::vector<int> vec(state.range(0));
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937());

    double before_mem = double(GetMemRam());
    double before_pate_file = double(GetMemPagefile());
    for (auto _ : state)
        for (auto k: vec)
            benchmark::DoNotOptimize(btree.insert(k));
    state.counters["RAM"] = double(GetMemRam()) - before_mem;
    state.counters["Pagefile"] =  double(GetMemPagefile()) - before_pate_file;
}


static void Ideal_B_lookup(benchmark::State& state) {
    using namespace frozenca;
    BTreeSet<int,60>btree{};
    std::vector<int> vec(state.range(0));
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937());

    double before_mem = double(GetMemRam());
    double before_pate_file = double(GetMemPagefile());
    for (auto k: vec)
        btree.insert(k);
    for (auto _ : state)
        for (auto k: vec)
            benchmark::DoNotOptimize(btree.find(k));
    state.counters["RAM"] = double(GetMemRam()) - before_mem;
    state.counters["Pagefile"] =  double(GetMemPagefile()) - before_pate_file;
}
static void set_lookup(benchmark::State& state) {

    std::set<int> btree;
    std::vector<int> vec(state.range(0));
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937());

    double before_mem = double(GetMemRam());
    double before_pate_file = double(GetMemPagefile());

    for (auto k: vec)
        btree.insert(k);
    for (auto _ : state)
        for (auto k: vec)
            benchmark::DoNotOptimize(btree.find(k));
    state.counters["RAM"] = double(GetMemRam()) - before_mem;
    state.counters["Pagefile"] =  double(GetMemPagefile()) - before_pate_file;
}




static int n = 2e7;

// BENCHMARK_TEMPLATE(BM_StringCreation, 2)->Arg(n) ->MinWarmUpTime(2) -> Iterations(1) ;
// BENCHMARK_TEMPLATE(BM_StringCreation, 5)->Arg(n)-> MinWarmUpTime(2) -> Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 10)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 16)->Arg(n)-> MinWarmUpTime(2) -> Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 28)->Arg(n)-> MinWarmUpTime(2) -> Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 32)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 34)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 36)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 48)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 50)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 60)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 64)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 66)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 128)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 240)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 512)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 1024)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 2048)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);
// BENCHMARK_TEMPLATE(BM_StringCreation, 4086)->Arg(n)->MinWarmUpTime(2) ->  Iterations(1);


// BENCHMARK(Ideal_B_insert) -> Arg(2)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(4)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(64)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(256)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(512)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(1024)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(4096)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(32768)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(1048576)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(4194304)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(16777216)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(33554432)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(Ideal_B_insert) -> Arg(67108864)->MinWarmUpTime(2)-> Iterations(1);
//
// BENCHMARK(set_insert) -> Arg(2)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(4)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(64)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(256)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(512)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(1024)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(4096)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(32768)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(1048576)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(4194304)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(16777216)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(33554432)->MinWarmUpTime(2)-> Iterations(1);
// BENCHMARK(set_insert) -> Arg(67108864)->MinWarmUpTime(2)-> Iterations(1);


BENCHMARK(Ideal_B_lookup) -> Arg(2)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(4)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(64)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(256)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(512)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(1024)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(4096)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(32768)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(1048576)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(4194304)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(16777216)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(33554432)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(Ideal_B_lookup) -> Arg(67108864)->MinWarmUpTime(2)-> Iterations(1);

BENCHMARK(set_lookup) -> Arg(2)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(4)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(64)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(256)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(512)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(1024)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(4096)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(32768)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(1048576)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(4194304)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(16777216)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(33554432)->MinWarmUpTime(2)-> Iterations(1);
BENCHMARK(set_lookup) -> Arg(67108864)->MinWarmUpTime(2)-> Iterations(1);



BENCHMARK_MAIN();
