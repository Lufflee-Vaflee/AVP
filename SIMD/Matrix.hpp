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

    template<std::size_t P>
    inline Matrix<N, P, element> operator*(Matrix<M, P, element> const& other) {
        Matrix<N, P, element, sel> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * P);

        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = 0; j < M; ++j) {
                for(std::size_t k = 0; k < P; ++k) {
                    result.m_data[i * N + k] += m_data[i * N + j] * other.m_data[j * M + k];
                }
            }
        }

        return result;
    }

    public:
    std::array<element, N * M> m_data;
};

template<std::size_t N_origin, std::size_t M_origin>
struct Span {

    constexpr Span(std::size_t N_offset, std::size_t M_offset, std::size_t N, std::size_t M) : 
        N_offset(N_offset),
        M_offset(M_offset),
        N(N),
        M(M) {}

    constexpr std::size_t get_i(std::size_t i) {
        return (N_offset + i) * M_origin + M_offset;
    }

    constexpr std::size_t get_ij(std::size_t i, std::size_t j) {
        return get_i(i) + j; 
    }

    constexpr auto splitByN() {
        std::size_t newN1 = N / 2;
        std::size_t newN2 = N - newN1;

        return std::pair(
            Span<N_origin, M_origin>(N_offset, M_offset, newN1, M),
            Span<N_origin, M_origin>(N_offset + newN1, M_offset, newN2, M)
        );
    }

    constexpr auto splitByM() {
        std::size_t newM1 = M / 2;
        std::size_t newM2 = M - newM1;

        return std::pair(
            Span<N_origin, M_origin>(N_offset, M_offset, N, newM1),
            Span<N_origin, M_origin>(N_offset, M_offset + newM1, N, newM2)
        );
    }

    std::size_t N_offset;
    std::size_t M_offset;
    std::size_t N;
    std::size_t M;
};

template<std::size_t N, std::size_t M, std::size_t P>
struct multTraits {

    constexpr multTraits(Span<N, P> C_Span, Span<N, M> A_Span, Span<M, P> B_Span) : 
        C_Span(C_Span),
        A_Span(A_Span),
        B_Span(B_Span) {}

    Span<N, P> C_Span;
    Span<N, M> A_Span;
    Span<M, P> B_Span;

    constexpr auto splitByN() {
        std::size_t newN1 = C_Span.N / 2;
        std::size_t newN2 = C_Span.N - newN1;

        std::size_t newN_offset = C_Span.N_offset + newN1;

        auto newC_Span1 = C_Span;
        auto newA_Span1 = A_Span;
        newC_Span1.N = newN1;
        newA_Span1.M = newN1;

        auto newC_Span2 = Span<N, P> {C_Span.N_offset + newN1, C_Span.M_offset, newN2, C_Span.M};
        auto newA_Span2 = Span<N, M> {A_Span.N_offset + newN1, A_Span.M_offset, newN2, A_Span.M};

        return std::pair(
            multTraits<N, M, P> {newC_Span1, newA_Span1, B_Span},
            multTraits<N, M, P> {newC_Span2, newA_Span2, B_Span}
        );
    }
};

template<std::size_t N, std::size_t M, typename element>
class Matrix<N, M, element, block> {
    static_assert(std::is_arithmetic_v<element>);
    public:

    Matrix() {};

    template<std::size_t P>
    inline Matrix<N, P, element> operator*(Matrix<M, P, element> const& other) {
        Matrix<N, P, element, block> result;

        std::memset(&result.m_data, 0, sizeof(element) * N * P);

        return result;
    }

    public:
    std::array<element, N * M> m_data;
};

template<std::size_t N, std::size_t M, std::size_t P, multTraits<N, M, P> traits, typename element>
void mult_body(element* C, element* A, element* B) {

    constexpr auto max = std::max(N, M, P);
    if constexpr (max == N) {


    } else if constexpr (max == M) {



    } else {

    }
}

}