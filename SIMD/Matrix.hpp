#pragma once 

#include <array>
#include <cstring>

namespace SIMD {

enum selector {
    naive,
    block,
    multithreaded
};

template<std::size_t N, std::size_t M, typename element, selector sel = naive>
class Matrix {
    static_assert(std::is_arithmetic_v<element>);
    public:

    Matrix() {};

    template<std::size_t L>
    inline Matrix<N, L, element> operator*(Matrix<M, L, element> const& other) {
        Matrix<N, L, element, sel> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * L);

        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                for(std::size_t k = 0; k < L; ++k) {
                    result.m_data[i * N + k] += m_data[i * N + j] * other.m_data[j * M + k];
                }
            }
        }

        return result;
    }

    public:
    std::array<element, N * M> m_data;
};

template<std::size_t N, std::size_t M, typename element>
class Matrix<N, M, element, block> {
    static_assert(std::is_arithmetic_v<element>);
    public:

    Matrix() {};

    template<std::size_t L>
    inline Matrix<N, L, element> operator*(Matrix<M, L, element> const& other) {
        Matrix<N, L, element, block> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * L);

        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                for(std::size_t k = 0; k < L; ++k) {
                    result.m_data[i * N + k] += m_data[i * N + j] * other.m_data[j * M + k];
                }
            }
        }



        return result;
    }

    public:
    std::array<element, N * M> m_data;
};

}