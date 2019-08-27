#pragma once
#include <algorithm>
#include <random>

#include "types.hpp"
namespace libtest {
class random_number_generator
{
public:
    random_number_generator() : mt{std::random_device{}()} {}
    template<typename T>
    auto gen(const T min, const T max) { return std::uniform_int_distribution<T>{min, max}(mt); }
    template<typename T>
    auto gen_vec(const T min, const T max) { return gen(min, max); }
    template<typename... Args>
    auto gen_vec(const usize n, Args... args)
    {
        std::vector<decltype(gen_vec(args...))> ans;
        for (usize i = 0; i < n; i++) { ans.push_back(gen_vec(args...)); }
        return ans;
    }
    template<typename T>
    std::pair<T, T> gen_pair(const T min, const T max) { return std::minmax(gen(min, max), gen(min, max)); }

private:
    std::mt19937_64 mt;
} rng;
}  // namespace libtest
