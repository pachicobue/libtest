#pragma once
#include <queue>
#include <vector>

#include "../utils/types.hpp"
namespace libtest {
struct HopcroftKarp
{
    std::vector<std::vector<usize>> graph;
    std::vector<int> dist, match;
    std::vector<bool> used, vv;

    HopcroftKarp(usize n, usize m) : graph(n), match(m, -1), used(n) {}

    void add_edge(usize u, usize v)
    {
        graph[u].push_back(v);
    }

    void bfs()
    {
        dist.assign(graph.size(), -1);
        std::queue<int> que;
        for (usize i = 0; i < graph.size(); i++) {
            if (!used[i]) {
                que.emplace(i);
                dist[i] = 0;
            }
        }

        while (!que.empty()) {
            int a = que.front();
            que.pop();
            for (auto& b : graph[a]) {
                int c = match[b];
                if (c >= 0 && dist[c] == -1) {
                    dist[c] = dist[a] + 1;
                    que.emplace(c);
                }
            }
        }
    }

    bool dfs(usize a)
    {
        vv[a] = true;
        for (auto& b : graph[a]) {
            int c = match[b];
            if (c < 0 || (!vv[c] && dist[c] == dist[a] + 1 && dfs(c))) {
                match[b] = (int)a;
                used[a]  = true;
                return (true);
            }
        }
        return (false);
    }

    usize bipartite_matching()
    {
        usize ret = 0;
        while (true) {
            bfs();
            vv.assign(graph.size(), false);
            usize flow = 0;
            for (usize i = 0; i < graph.size(); i++) {
                if (!used[i] && dfs(i)) ++flow;
            }
            if (flow == 0) return (ret);
            ret += flow;
        }
    }
};
}  // namespace libtest
