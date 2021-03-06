#pragma once
#include <fstream>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
#include "reference.hpp"
namespace libtest {
struct all_pair_shortest_path
{
    static constexpr const char* path       = "all_pair_shortest_path";
    static constexpr const char* name       = "All Pair Shortest Path (Positive Weight)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto e_max = constraints::e_max;
        constexpr auto c_min = constraints::c_min, c_max = constraints::c_max;
        printer pr{input_file};
        const auto v = rng.gen(v_min, v_max);
        const auto e = rng.gen(v - 1, e_max);
        pr.println(v, e);
        const auto g = random_cost_graph(v, e, c_min, c_max, false);
        for (usize i = 0; i < v; i++) {
            for (const auto& e : g.edge[i]) { pr.println(e.from, e.to, e.cost); }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [v, e] = sc.read_vals<usize, usize>();
        cost_graph<ll> g(v);
        for (usize i = 0; i < e; i++) {
            const auto [u, v, c] = sc.read_vals<usize, usize, ll>();
            g.add_edge(u, v, c);
        }
        const auto d = apsp(g);
        for (const auto& l : d) { pr.println(l); }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto [v, e] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < v; i++) {
            const auto gen_d = gen_sc.read<ll>();
            const auto sol_d = sol_sc.may_read<ll>();
            if (gen_d > small_constraints::c_max * static_cast<ll>(small_constraints::v_max)) {
                if (sol_d <= small_constraints::c_max * static_cast<ll>(small_constraints::v_max)) { return false; }
            } else {
                if (gen_d != sol_d) { return false; }
            }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 50;
        static constexpr usize e_max = 200;
        static constexpr ll c_min = 0, c_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 300;
        static constexpr usize e_max = 10000;
        static constexpr ll c_min = 0, c_max = 10000;
    };
};
}  // namespace libtest
