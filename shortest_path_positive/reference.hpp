#pragma once
#include <limits>
#include <queue>

#include "../utils/graph.hpp"
#include "../utils/inf.hpp"
namespace libtest {
template<typename T>
std::vector<T> dijkstra(const cost_graph<T>& g, const usize r)
{
    const usize v = g.v;
    using P       = std::pair<ll, usize>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> q;
    std::vector<T> d(v, inf<T>);
    d[r] = 0, q.push({0LL, r});
    while (not q.empty()) {
        const auto v = q.top().second;
        q.pop();
        for (const auto& e : g.edge[v]) {
            if (d[e.to] <= d[v] + e.cost) { continue; }
            d[e.to] = d[v] + e.cost, q.push({d[e.to], e.to});
        }
    }
    return d;
}

}  // namespace libtest
