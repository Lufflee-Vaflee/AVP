#include "NoSIMD/lib.hpp"
#include "Intrinsics/lib.hpp"
#include "SIMD/MatrixRec.hpp"
#include "SIMD/NaiveMatrix.hpp"

#include "Benchmark.hpp"

#include <chrono>
#include <iostream>


int main() {

    //SIMD::RecMatrix<8, 8, int> a;
    //SIMD::RecMatrix<8, 8, int> b;
    SIMD::NaiveMatrix<100, 200, unsigned> a;
    SIMD::NaiveMatrix<200, 100, unsigned> b;

    SIMD::RecMatrix<100, 200, unsigned> d;
    SIMD::RecMatrix<200, 100, unsigned> e;

    a.fillWithRand();
    b.fillWithRand();

    d.m_data = a.m_data;
    e.m_data = b.m_data;

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    auto c = a * b;
    auto l = d * e;

    std::cout << c << std::endl;
    std::cout << l << std::endl;

    bool isEqual = (l.m_data == c.m_data);

    std::cout << '\n' << (isEqual ? "IS EQUAL!!!" : "IS NOT EQUAL (((") << '\n';

    return c.m_data[13];
}