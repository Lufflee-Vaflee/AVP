#pragma once

#include <tuple>


namespace SIMD
{

struct multTraits {

    constexpr multTraits(std::size_t N, std::size_t M, std::size_t P, std::size_t M_origin, std::size_t P_origin) :
        N(N),
        M(M),
        P(P),
        M_origin(M_origin),
        P_origin(P_origin) {}

    std::size_t N;
    std::size_t M;
    std::size_t P;
    std::size_t M_origin;
    std::size_t P_origin;
};

} // namespace SIMD
