#pragma once
#include <fstream>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct lowest_common_ancestor
{
    static constexpr const char* path       = "lowest_common_ancestor";
    static constexpr const char* name       = "Lowest Common Ancestor";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto v = rng.gen(v_min, v_max);
        const auto q = rng.gen(q_min, q_max);
        pr.println(v, q);
        const auto g = random_graph(v, v - 1, true);
        for (usize i = 0; i < v; i++) {
            for (const usize to : g.edge[i]) {
                if (i < to) { pr.println(i, to); }
            }
        }
        for (usize i = 0; i < q; i++) {
            const auto p = rng.gen_pair(0UL, v - 1);
            pr.println(p.first, p.second);
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [v, q] = sc.read_vals<usize, usize>();
        graph g(v);
        for (usize i = 0; i < v - 1; i++) {
            const auto [u, v] = sc.read_vals<usize, usize>();
            g.add_edge(u, v, true);
        }
        std::vector<usize> depth(v, 0), par(v, v);
        auto dfs = [&](auto&& self, const usize s, const usize p) -> void {
            for (const usize to : g.edge[s]) {
                if (to == p) { continue; }
                depth[to] = depth[s] + 1, par[to] = s, self(self, to, s);
            }
        };
        dfs(dfs, 0, v);
        for (usize i = 0; i < q; i++) {
            auto [u, v] = sc.read_vals<usize, usize>();
            while (true) {
                if (depth[u] > depth[v]) { std::swap(u, v); }
                while (depth[u] < depth[v]) { v = par[v]; }
                if (u == v) {
                    break;
                } else {
                    u = par[u];
                }
            }
            pr.println(u);
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto [v, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            const auto gen_a = gen_sc.read<usize>();
            const auto sol_a = sol_sc.may_read<usize>();
            if (gen_a != sol_a) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
    };
};
}  // namespace libtest
