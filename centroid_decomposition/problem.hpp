#pragma once
#include <fstream>
#include <map>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct centroid_decomposition
{
    static constexpr const char* path       = "centroid_decomposition";
    static constexpr const char* name       = "Centroid Decomposition";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto v = rng.gen(v_min, v_max);
        pr.println(v);
        const auto g = random_graph(v, v - 1, true);
        for (usize i = 0; i < v; i++) {
            for (const auto to : g.edge[i]) {
                if (i < to) { pr.println(i, to); }
            }
        }
    }
    static void generate_output(std::ifstream&, std::ofstream& output_file)
    {
        printer pr{output_file};
        pr.println("No Output");
    }
    static bool judge(std::ifstream& input_file, std::ifstream&, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, sol_sc{solution_output_file};
        const auto v = in_sc.read<usize>();
        std::vector<std::vector<usize>> t(v);
        for (usize i = 0; i < v - 1; i++) {
            const auto [u, v] = in_sc.read_vals<usize, usize>();
            t[u].push_back(v), t[v].push_back(u);
        }
        std::vector<std::vector<usize>> ct(v);
        for (usize i = 0; i < v - 1; i++) {
            const auto [u, v] = sol_sc.may_read_vals<usize, usize>();
            if (not u or not v) { return false; }
            ct[*u].push_back(*v);
        }
        std::vector<usize> in(v, 0);
        for (usize i = 0; i < v; i++) {
            for (const usize to : ct[i]) { in[to]++; }
        }
        usize r = v;
        for (usize i = 0; i < v; i++) {
            if (in[i] == 0) { r = i; }
        }
        std::vector<bool> used(v, false);
        bool ok  = true;
        auto dfs = [&](auto&& self, const usize c) -> usize {
            used[c]   = true;
            usize sum = 1;
            std::vector<usize> sub;
            for (const usize to : ct[c]) {
                if (used[to]) { continue; }
                const usize s = self(self, to);
                sub.push_back(s), sum += s;
            }
            for (const usize sz : sub) {
                if (sz * 2 > sum) { ok = false; }
            }
            return sum;
        };
        dfs(dfs, r);
        return ok;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 1000;
    };
};
}  // namespace libtest
