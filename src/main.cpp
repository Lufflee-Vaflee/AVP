#include "NoSIMD/lib.hpp"
#include "Intrinsics/lib.hpp"
#include "SIMD/lib.hpp"

#include "Benchmark.hpp"

#include <chrono>
#include <iostream>

bool check(int a, int b, int c);


int main() {
    auto bench = Benchmark(check);

    auto result = bench(1, 2, 3);

    return 0;
}