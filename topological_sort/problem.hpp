#pragma once
#include <fstream>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct topological_sort
{
    static constexpr const char* path       = "topological_sort";
    static constexpr const char* name       = "Topological Sort";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto e_max = constraints::e_max;
        printer pr{input_file};
        const auto v = rng.gen(v_min, v_max);
        const auto e = rng.gen(v - 1, e_max);
        pr.println(v, e);
        const auto g = random_dag(v, e);
        for (usize i = 0; i < v; i++) {
            for (const usize to : g.edge[i]) { pr.println(i, to); }
        }
    }
    static void generate_output(std::ifstream&, std::ofstream& output_file)
    {
        printer pr{output_file};
        pr.println("No output");
    }
    static bool judge(std::ifstream& input_file, std::ifstream&, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, sol_sc{solution_output_file};
        const auto [v, e] = in_sc.read_vals<usize, usize>();
        const auto ord    = sol_sc.may_read_vec<usize>(v);
        std::vector<usize> comp(v);
        for (usize i = 0; i < v; i++) {
            if (not ord[i]) { return false; }
            comp[*ord[i]] = i;
        }
        for (usize i = 0; i < e; i++) {
            const auto [from, to] = in_sc.read_vals<usize, usize>();
            if (comp[from] > comp[to]) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 10;
        static constexpr usize e_max = 20;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_max = 1000;
    };
};
}  // namespace libtest
