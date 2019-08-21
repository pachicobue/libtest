#pragma once
#include <algorithm>
#include <random>
#include "types.hpp"
namespace libtest {
class Rng
{
public:
    Rng() : Rng(std::random_device{}()) {}
    Rng(const u64 seed) : mt{seed} {}
    u64 operator()() { return mt(); }
    template <typename Int>
    Int uniformInt(const Int min, const Int max) { return std::uniform_int_distribution<Int>{min, max}(mt); }
    bool uniformBool() { return static_cast<bool>(uniformInt<int>(0, 1)); }
    template <typename Real>
    Real uniformReal(const Real min, const Real max) { return std::uniform_real_distribution<Real>{min, max}(mt); }
    template <typename Int>
    std::pair<Int, Int> uniformIntPair(const Int min, const Int max) { return std::minmax(uniformInt(min, max), uniformInt(min, max)); }
    template <typename Int>
    std::vector<Int> uniformIntVec(const std::size_t N, const Int min, const Int max)
    {
        std::vector<Int> v(N);
        for (std::size_t i = 0; i < N; i++) { v[i] = uniformInt(min, max); }
        return v;
    }
    template <typename Real>
    std::vector<Real> uniformRealVec(const std::size_t N, const Real min, const Real max)
    {
        std::vector<Real> v(N);
        for (std::size_t i = 0; i < N; i++) { v[i] = uniformReal(min, max); }
        return v;
    }

private:
    std::mt19937_64 mt;
} rng;
}  // namespace libtest
