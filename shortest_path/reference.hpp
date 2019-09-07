#pragma once
#include "../utils/graph.hpp"
#include "../utils/inf.hpp"
namespace libtest {
template<typename T>
std::vector<T> bellman_ford(const cost_graph<T>& g, const usize r)
{
    const usize v = g.v;
    std::vector<T> d(v, inf<T>);
    d[r] = 0;
    for (usize i = 0; i < 2 * v; i++) {
        for (usize u = 0; u < v; u++) {
            for (const auto& e : g.edge[u]) {
                if (d[e.from] != inf<T> and d[e.to] > d[e.from] + e.cost) {
                    if (d[e.from] == -inf<T>) {
                        d[e.to] = -inf<T>;
                    } else {
                        d[e.to] = d[e.from] + e.cost;
                        if (i >= v) { d[e.to] = -inf<T>; }
                    }
                }
            }
        }
    }
    return d;
}

}  // namespace libtest
