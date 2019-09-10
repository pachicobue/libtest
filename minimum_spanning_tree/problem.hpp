#pragma once
#include <fstream>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct minimum_spanning_tree
{
    static constexpr const char* path       = "minimum_spanning_tree";
    static constexpr const char* name       = "Minimum Spanning Tree";
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
        const auto g = random_cost_graph(v, e, c_min, c_max, true);
        for (usize i = 0; i < v; i++) {
            for (const auto& e : g.edge[i]) {
                if (i < e.to) { pr.println(i, e.to, e.cost); }
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [v, e] = sc.read_vals<usize, usize>();
        using P           = std::pair<usize, usize>;
        using E           = std::pair<ll, P>;
        std::vector<E> es;
        for (usize i = 0; i < e; i++) {
            const auto [f, t, c] = sc.read_vals<usize, usize, ll>();
            es.push_back({c, {f, t}});
        }
        std::sort(es.begin(), es.end());
        ll ans = 0;
        unionfind uf{v};
        for (const auto& pp : es) {
            const ll c    = pp.first;
            const usize f = pp.second.first, t = pp.second.second;
            if (uf.same(f, t)) { continue; }
            uf.unite(t, f), ans += c;
        }
        pr.println(ans);
    }
    static bool judge(std::ifstream&, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        return gen_sc.read<ll>() == sol_sc.may_read<ll>();
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_max = 1000;
        static constexpr ll c_min = -100, c_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 10000;
        static constexpr usize e_max = 100000;
        static constexpr ll c_min = -10000, c_max = 10000;
    };
};
}  // namespace libtest
