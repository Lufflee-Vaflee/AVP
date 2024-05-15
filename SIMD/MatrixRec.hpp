#pragma once 

#include <array>
#include <cstring>

#include "Config.hpp"
#include <iomanip>

#include "MultTraits.hpp"

namespace SIMD {

constexpr auto LowerBound = L1_SIZE / (2 * 3 * 2);  // 2 - commands and data, 3 - number of matrixes, 2 - vodoo num for environment needs :)

unsigned* debug;

template<multTraits traits, typename element>
void plain_mult(element* C, element* A, element* B) {
    
    std::cout << "plain mult entrance\n";
    std::cout << "C: " << (std::size_t)C / sizeof(element) << '\n';
    std::cout << "A: " << (std::size_t)A / sizeof(element) << '\n';
    std::cout << "B: " << (std::size_t)B / sizeof(element) << '\n';
    std::cout << "N: " << traits.N << '\n';
    std::cout << "M: " << traits.M << '\n';
    std::cout << "P: " << traits.P << '\n';


    for(std::size_t i = 0; i < traits.N; ++i) {
        for(std::size_t j = 0; j < traits.M; ++j) {
            for(std::size_t k = 0; k < traits.P; ++k) {
                C[i * traits.P_origin + k] += A[i * traits.M_origin + j] * B[j * traits.P_origin + k];
            }
        }
    }

    std::cout << '\n';
    for(std::size_t i = 0; i < 10; ++i) {
        for(std::size_t j = 0; j < 10; ++j) {
            std::cout << std::setw(5) << debug[i * 10 + j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

template<multTraits traits, typename element>
void mult_body(element* C, element* A, element* B) {

    constexpr auto max = std::max(std::max(traits.N, traits.M), traits.P);

    if constexpr (traits.N * traits.M * traits.P * sizeof(element) < LowerBound) {       //exit from recursion based on L1 size
        plain_mult<traits, element>(C, A, B);
        return;
    } else {

        if constexpr (max == traits.N) {
            constexpr multTraits newTraits1 {traits.N / 2, traits.M, traits.P, traits.M_origin, traits.P_origin};
            constexpr multTraits newTraits2 {traits.N - newTraits1.N, traits.M, traits.P, traits.M_origin, traits.P_origin};


            mult_body<newTraits1, element>(C, A, B);
            mult_body<newTraits2, element>(C + newTraits1.N * traits.P_origin, A + newTraits1.N * traits.M_origin, B);
            return;
        } else if constexpr (max == traits.P) {
            constexpr multTraits newTraits1 {traits.N, traits.M, traits.P / 2, traits.M_origin, traits.P_origin};
            constexpr multTraits newTraits2 {traits.N, traits.M, traits.P - newTraits1.P, traits.M_origin, traits.P_origin};

 
            mult_body<newTraits1, element>(C, A, B);
            mult_body<newTraits2, element>(C + newTraits1.P, A, B + newTraits1.P);
            return;
        } else {
            constexpr multTraits newTraits1 {traits.N, traits.M / 2, traits.P, traits.M_origin, traits.P_origin};
            constexpr multTraits newTraits2 {traits.N, traits.M - newTraits1.M, traits.P, traits.M_origin, traits.P_origin};

            mult_body<newTraits1, element>(C, A, B);
            mult_body<newTraits2, element>(C, A + newTraits1.M, B + newTraits1.M * traits.P_origin);
            return;
        }
    }
}

template<std::size_t N, std::size_t M, typename element>
class RecMatrix {
    static_assert(std::is_arithmetic_v<element>);
    public:

    RecMatrix() {
        debug = (unsigned*)&m_data;
    };

    template<std::size_t P>
    inline RecMatrix<N, P, element> operator*(RecMatrix<M, P, element> const& other) {
        RecMatrix<N, P, element> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * P);

        constexpr auto start_traits = multTraits(N, M, P, M, P);

        mult_body<start_traits, element>((element*)&result.m_data, (element*)&m_data, (element*)&other.m_data);

        return result;
    }

    friend std::ostream& operator<< (std::ostream& stream, const RecMatrix& matrix) {
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