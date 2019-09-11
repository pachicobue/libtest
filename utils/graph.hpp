#pragma once
#include <cassert>
#include <vector>

#include "random.hpp"
#include "types.hpp"
#include "union_find.hpp"
namespace libtest {
struct graph
{
    graph(const usize v) : edge(v), v{v} {}
    void add_edge(const usize i, const usize j, const bool bi = false)
    {
        e++, edge[i].push_back(j);
        if (bi) { e++, edge[j].push_back(i); }
    }
    std::vector<std::vector<usize>> edge;
    const usize v;
    usize e = 0;
};
template<typename T>
struct cost_graph
{
    struct p
    {
        usize from, to;
        T cost;
    };
    cost_graph(const usize v) : edge(v), v{v} {}
    void add_edge(const usize i, const usize j, const T c, const bool bi = false)
    {
        e++, edge[i].push_back(p{i, j, c});
        if (bi) { e++, edge[j].push_back(p{j, i, c}); }
    }
    std::vector<std::vector<p>> edge;
    const usize v;
    usize e = 0;
};
graph random_graph(const usize v, const usize e, const bool bi = false)
{
    graph g{v};
    unionfind uf{v};
    for (usize i = 0; i < v - 1;) {
        auto p = rng.gen_pair(0UL, v - 1);
        if (rng.gen(0, 1)) { std::swap(p.first, p.second); }
        if (uf.same(p.first, p.second)) { continue; }
        uf.unite(p.first, p.second), g.add_edge(p.first, p.second, bi), i++;
    }
    for (usize i = v - 1; i < e;) {
        auto p = rng.gen_pair(0UL, v - 1);
        if (rng.gen(0, 1)) { std::swap(p.first, p.second); }
        if (p.first == p.second) { continue; }
        g.add_edge(p.first, p.second, bi), i++;
    }
    return g;
}
template<typename T>
cost_graph<T> random_cost_graph(const usize v, const usize e, const T c_min, const T c_max, const bool bi = false)
{
    cost_graph<T> g{v};
    unionfind uf{v};
    for (usize i = 0; i < v - 1;) {
        auto p = rng.gen_pair(0UL, v - 1);
        if (rng.gen(0, 1)) { std::swap(p.first, p.second); }
        const auto c = rng.gen(c_min, c_max);
        if (uf.same(p.first, p.second)) { continue; }
        uf.unite(p.first, p.second), g.add_edge(p.first, p.second, c, bi), i++;
    }
    for (usize i = v - 1; i < e;) {
        auto p = rng.gen_pair(0UL, v - 1);
        if (rng.gen(0, 1)) { std::swap(p.first, p.second); }
        const auto c = rng.gen(c_min, c_max);
        if (p.first == p.second) { continue; }
        g.add_edge(p.first, p.second, c, bi), i++;
    }
    return g;
}
graph random_dag(const usize v, const usize e)
{
    std::vector<usize> ind(v);
    std::iota(ind.begin(), ind.end(), 0);
    std::shuffle(ind.begin(), ind.end(), rng);
    graph g{v};
    unionfind uf{v};
    for (usize i = 0; i < v - 1;) {
        const auto q                    = rng.gen_pair(0UL, v - 1);
        const std::pair<usize, usize> p = {ind[q.first], ind[q.second]};
        if (uf.same(p.first, p.second)) { continue; }
        uf.unite(p.first, p.second), g.add_edge(p.first, p.second), i++;
    }
    for (usize i = v - 1; i < e;) {
        const auto q                    = rng.gen_pair(0UL, v - 1);
        const std::pair<usize, usize> p = {ind[q.first], ind[q.second]};
        if (p.first == p.second) { continue; }
        g.add_edge(p.first, p.second), i++;
    }
    return g;
}
}  // namespace libtest
