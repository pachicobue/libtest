#pragma once
#include <fstream>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct bridges
{
    static constexpr const char* path       = "bridges";
    static constexpr const char* name       = "Bridges";
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
        const auto g = random_graph(v, e, true);
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
        const auto [v, e] = sc.read_vals<usize, usize>();
        using P           = std::pair<usize, usize>;
        std::vector<P> edge;
        for (usize i = 0; i < e; i++) {
            const auto [u, v] = sc.read_vals<usize, usize>();
            edge.push_back({u, v});
        }
        std::vector<P> ans;
        for (usize i = 0; i < e; i++) {
            unionfind uf(v);
            for (usize j = 0; j < e; j++) {
                if (i == j) { continue; }
                const auto [u, v] = edge[j];
                uf.unite(u, v);
            }
            if (uf.size_of(0) < v) { ans.push_back(edge[i]); }
        }
        std::sort(ans.begin(), ans.end());
        pr.println(ans.size());
        for (const auto& p : ans) { pr.println(p.first, p.second); }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto gen_n = gen_sc.read<usize>();
        const auto sol_n = sol_sc.may_read<usize>();
        if (gen_n != sol_n) { return false; }
        for (usize i = 0; i < gen_n; i++) {
            const auto [gen_u, gen_v] = gen_sc.read_vals<usize, usize>();
            const auto [sol_u, sol_v] = sol_sc.may_read_vals<usize, usize>();
            if (gen_u != sol_u or gen_v != sol_v) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_max = 110;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 1000;
        static constexpr usize e_max = 1010;
    };
};
}  // namespace libtest
