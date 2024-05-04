#pragma once

#include <chrono>

template<typename R, typename... Args>
class Benchmark {
    public:
    using signature = R(*)(Args...);

    Benchmark(signature function) :
        m_function(function) {}

    auto operator()(Args&&... args) {
        std::chrono::high_resolution_clock clk;
        auto start = clk.now();
        R result = m_function(std::forward<Args>(args)...);
        auto end = clk.now();
        return std::pair(result, end - start);
    }

    private:
    signature m_function;
};

//User-defined CTAD
template <typename R, typename... Args>
Benchmark(R(*)(Args...)) -> Benchmark<R, Args...>;