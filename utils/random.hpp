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
    std::pair<Int, Int> uniform_int_pair(const Int min, const Int max) { return std::minmax(uniformInt(min, max), uniformInt(min, max)); }
    template<typename Int>
    std::vector<Int> uniform_int_vec(const std::size_t N, const Int min, const Int max)
    {
        std::vector<Int> v(N);
        for (std::size_t i = 0; i < N; i++) { v[i] = uniformInt(min, max); }
        return v;
    }
    template<typename Real>
    std::vector<Real> uniform_real_vec(const std::size_t N, const Real min, const Real max)
    {
        std::vector<Real> v(N);
        for (std::size_t i = 0; i < N; i++) { v[i] = uniformReal(min, max); }
        return v;
    }

private:
    std::mt19937_64 mt;
} g_rng;
}  // namespace libtest
