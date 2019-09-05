#pragma once
#include <numeric>
#include <vector>

#include "types.hpp"
namespace libtest {
class unionfind
{
public:
    unionfind(const usize sz) : sz{sz}, rt(sz), comp_sz(sz, 1) { std::iota(rt.begin(), rt.end(), 0); }
    usize root(const usize a) { return rt[a] == a ? a : rt[a] = root(rt[a]); }
    bool same(const usize a, const usize b) { return root(a) == root(b); }
    bool unite(usize a, usize b)
    {
        a = root(a), b = root(b);
        if (a == b) { return false; }
        if (comp_sz[a] < comp_sz[b]) { std::swap(a, b); }
        return comp_sz[a] += comp_sz[b], rt[b] = a, true;
    }
    usize size() const { return sz; }
    usize size_of(const usize a) { return comp_sz[root(a)]; }

private:
    const usize sz;
    std::vector<usize> rt, comp_sz;
};
}  // namespace libtest
