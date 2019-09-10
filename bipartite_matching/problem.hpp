#pragma once
#include <fstream>
#include <set>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
#include "reference.hpp"

namespace libtest {
struct bipartite_matching
{
    static constexpr const char* path       = "bipartite_matching";
    static constexpr const char* name       = "Bipartite Maximum Matching";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto e_min = constraints::v_min, e_max = constraints::v_max;
        printer pr{input_file};
        const auto v1 = rng.gen(v_min, v_max);
        const auto v2 = rng.gen(v_min, v_max);
        const auto e  = rng.gen(e_min, std::min(v1 * v2, e_max));
        pr.println(v1, v2, e);
        using P = std::pair<usize, usize>;
        std::set<P> st;
        for (usize i = 0; i < e;) {
            const auto u = rng.gen(0UL, v1 - 1);
            const auto v = rng.gen(0UL, v2 - 1);
            if (st.find({u, v}) != st.end()) { continue; }
            pr.println(u, v), st.insert({u, v}), i++;
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [v1, v2, e] = sc.read_vals<usize, usize, usize>();
        HopcroftKarp hk(v1, v2);
        for (usize i = 0; i < e; i++) {
            const auto [u, v] = sc.read_vals<usize, usize>();
            hk.add_edge(u, v);
        }
        pr.println(hk.bipartite_matching());
    }
    static bool judge(std::ifstream&, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        return gen_sc.read<usize>() == sol_sc.may_read<usize>();
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_min = 2, e_max = 200;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 1000;
        static constexpr usize e_min = 2, e_max = 3000;
    };
};
}  // namespace libtest
