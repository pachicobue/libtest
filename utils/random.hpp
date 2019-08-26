#pragma once
#include <algorithm>
#include <random>

#include "types.hpp"
namespace libtest {
class rng
{
public:
    rng() : rng(std::random_device{}()) {}
    rng(const u64 seed) : mt{seed} {}
    u64 operator()() { return mt(); }
    template<typename Int>
    Int uniform_int(const Int min, const Int max) { return std::uniform_int_distribution<Int>{min, max}(mt); }
    bool uniform_bool() { return static_cast<bool>(uniform_int<int>(0, 1)); }
    template<typename Real>
    Real uniform_real(const Real min, const Real max) { return std::uniform_real_distribution<Real>{min, max}(mt); }
    template<typename Int>
    std::pair<Int, Int> uniform_int_pair(const Int min, const Int max, const bool sorted = true) { return sorted ? std::minmax(uniform_int(min, max), uniform_int(min, max)) : std::pair<const Int&, const Int&>{uniform_int(min, max), uniform_int(min, max)}; }
    template<typename Int>
    std::vector<Int> uniform_int_vec(const usize N, const Int min, const Int max)
    {
        std::vector<Int> v(N);
        for (usize i = 0; i < N; i++) { v[i] = uniform_int(min, max); }
        return v;
    }
    template<typename Real>
    std::vector<Real> uniform_real_vec(const usize N, const Real min, const Real max)
    {
        std::vector<Real> v(N);
        for (usize i = 0; i < N; i++) { v[i] = uniform_real(min, max); }
        return v;
    }

private:
    std::mt19937_64 mt;
} g_rng;
}  // namespace libtest
