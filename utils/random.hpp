#pragma once
#include <algorithm>
#include <random>

#include "types.hpp"
namespace libtest {
class random_number_generator
{
    using rng_type = std::mt19937_64;

public:
    using result_type = rng_type::result_type;
    static constexpr result_type min() { return rng_type::min(); }
    static constexpr result_type max() { return rng_type::max(); }
    random_number_generator() : mt{std::random_device{}()} {}
    result_type operator()() { return mt(); }
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
    template<typename T>
    T gen_prime(const T min, const T max)
    {
        for (usize i = 0; i < 10000; i++) {
            const auto n = gen(min, max);
            if (isprime(n)) { return n; }
        }
        return 0;
    }

private:
    template<typename T>
    bool isprime(const T n)
    {
        for (T i = 2; i * i <= n; i++) {
            if (n % i == 0) { return false; }
        }
        return true;
    }

    std::mt19937_64 mt;
} rng;
}  // namespace libtest
