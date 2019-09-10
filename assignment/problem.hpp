#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct assignment
{
    static constexpr const char* path       = "assignment";
    static constexpr const char* name       = "Assignment Problem";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        pr.println(n);
        const auto cost = rng.gen_vec(n, n, v_min, v_max);
        for (const auto& l : cost) { pr.println(l); }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto n    = sc.read<usize>();
        const auto cost = sc.read_vec<ll>(n, n);
        std::vector<usize> ind(n);
        std::iota(ind.begin(), ind.end(), 0);
        ll min = std::numeric_limits<ll>::max();
        std::vector<usize> ans;
        do {
            ll sum = 0;
            for (usize i = 0; i < n; i++) { sum += cost[i][ind[i]]; }
            if (min > sum) { min = sum, ans = ind; }
        } while (std::next_permutation(ind.begin(), ind.end()));
        pr.println(ans);
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto n     = in_sc.read<usize>();
        const auto cost  = in_sc.read_vec<ll>(n, n);
        const auto gen_v = gen_sc.read_vec<usize>(n);
        const auto sol_v = sol_sc.may_read_vec<usize>(n);
        if (not sol_v.back()) { return false; }
        ll gen_cost = 0, sol_cost = 0;
        for (usize i = 0; i < n; i++) { gen_cost += cost[i][gen_v[i]], sol_cost += cost[i][*sol_v[i]]; }
        return gen_cost == sol_cost;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 8;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 300;
        static constexpr ll v_min = -100000, v_max = 100000;
    };
};
}  // namespace libtest
