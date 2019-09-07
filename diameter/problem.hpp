#pragma once
#include <fstream>
#include <map>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct diameter
{
    static constexpr const char* path       = "diameter";
    static constexpr const char* name       = "Diameter";
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
            for (const usize to : g.edge[i]) {
                if (i < to) { pr.println(i, to); }
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto v = sc.read<usize>();
        graph g(v);
        for (usize i = 0; i < v - 1; i++) {
            const auto [u, v] = sc.read_vals<usize, usize>();
            g.add_edge(u, v, true);
        }
        usize max = 0;
        for (usize i = 0; i < v; i++) {
            std::vector<usize> d(v, 0);
            auto dfs = [&](auto&& self, const usize s, const usize p) -> void {
                for (const usize to : g.edge[s]) {
                    if (to == p) { continue; }
                    d[to] = d[s] + 1, self(self, to, s);
                }
            };
            dfs(dfs, i, v);
            for (usize j = 0; j < v; j++) { max = std::max(max, d[j]); }
        }
        pr.println(max + 1);
        pr.println(std::vector<std::string>(max + 1, "dummy"));
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto v = in_sc.read<usize>();
        using P      = std::pair<usize, usize>;
        std::map<P, int> edge;
        for (usize i = 0; i < v - 1; i++) {
            const auto [u, v] = in_sc.read_vals<usize, usize>();
            edge[std::minmax(u, v)]++;
        }
        const auto gen_n = gen_sc.read<usize>();
        const auto sol_n = sol_sc.may_read<usize>();
        if (gen_n != sol_n) { return false; }
        const auto pp = sol_sc.may_read<usize>();
        if (not pp) { return false; }
        for (usize i = 0, p = *pp; i < gen_n - 1; i++) {
            const auto u = sol_sc.may_read<usize>();
            if (not u) { return false; }
            const auto next = *u;
            if (edge[std::minmax(p, next)] == 0) { return false; }
            edge[std::minmax(p, next)]--, p = next;
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 10000;
    };
};
}  // namespace libtest
