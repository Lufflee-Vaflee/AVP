#pragma once 

#include <array>
#include <cstring>
#include <iomanip>

#include "Config.hpp"

namespace SIMD 
{

template<std::size_t N, std::size_t M, typename element>
class NaiveMatrix {
    static_assert(std::is_arithmetic_v<element>);
    public:

    NaiveMatrix() {};

    template<std::size_t P>
    inline NaiveMatrix<N, P, element> operator*(NaiveMatrix<M, P, element> const& other) {
        NaiveMatrix<N, P, element> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * P);

        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                for(std::size_t k = 0; k < P; ++k) {
                    result.m_data[i * N + k] += m_data[i * M + j] * other.m_data[j * P + k];
                }
            }
        }

        return result;
    }

    void fillWithRand() {
        std::srand(time(0));
        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                m_data[i * M + j] = std::rand() % 5;
            }
        }
    }

    friend std::ostream& operator<< (std::ostream& stream, const NaiveMatrix& matrix) {
        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                stream << std::setw(5) << matrix.m_data[i * M + j];
            }
            stream << '\n';
        }
    }


    public:
    std::array<element, N * M> m_data;
};

}