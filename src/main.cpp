#include "SIMD/MatrixRec.hpp"
#include "SIMD/NaiveMatrix.hpp"

#include <chrono>
#include <iostream>

void test_rec_64();
void test_naive_64();
void test_rec_32();
void test_naive_32();

int main() {
    test_naive_64();
    test_rec_64();
    test_naive_32();
    test_rec_32();

    return 0;
}

void test_naive_64() {
    SIMD::NaiveMatrix<2000, 2000, double> a;
    SIMD::NaiveMatrix<2000, 2000, double> b;

    a.fillWithRand();
    b.fillWithRand();

    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    auto c = a * b;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.(naive64)\n";
}


void test_rec_64() {
    SIMD::RecMatrix<2000, 2000, double> a;
    SIMD::RecMatrix<2000, 2000, double> b;

    a.fillWithRand();
    b.fillWithRand();

    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    auto c = a * b;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.(rec64)\n";
}

void test_naive_32() {
    SIMD::NaiveMatrix<2000, 2000, float> a;
    SIMD::NaiveMatrix<2000, 2000, float> b;

    a.fillWithRand();
    b.fillWithRand();

    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    auto c = a * b;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.(naive32)\n";
}


void test_rec_32() {
    SIMD::RecMatrix<2000, 2000, float> a;
    SIMD::RecMatrix<2000, 2000, float> b;

    a.fillWithRand();
    b.fillWithRand();

    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    auto c = a * b;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.(rec32)\n";
}