#pragma once
#include "../utils/graph.hpp"
#include "../utils/inf.hpp"
namespace libtest {
template<typename T>
std::vector<std::vector<T>> apsp(const cost_graph<T>& g)
{
    const usize v = g.v;
    std::vector<std::vector<T>> d(v, std::vector<T>(v, inf<T>));
    for (usize i = 0; i < v; i++) {
        d[i][i] = 0;
        for (const auto& e : g.edge[i]) { d[e.from][e.to] = std::min(d[e.from][e.to], e.cost); }
    }
    for (usize k = 0; k < v; k++) {
        for (usize i = 0; i < v; i++) {
            for (usize j = 0; j < v; j++) { d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]); }
        }
    }
    return d;
}

}  // namespace libtest
