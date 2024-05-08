#include "NoSIMD/lib.hpp"
#include "Intrinsics/lib.hpp"
#include "SIMD/lib.hpp"

#include "Benchmark.hpp"

#include <chrono>
#include <iostream>


int main() {

    SIMD::Matrix<3, 4, int> a;
    SIMD::Matrix<4, 5, int> b;

    auto c = a * b;

    return 0;
}