#include <iostream>
#include "NoSIMD/lib.hpp"
#include "Intrinsics/lib.hpp"
#include "SIMD/lib.hpp"





int main() {
    NoSIMD::foo();
    SIMD::foo();
    Intrinsics::foo();

    return 0;
}