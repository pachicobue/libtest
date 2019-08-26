#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct assignment
{
    static constexpr const char* path       = "assignment";
    static constexpr const char* name       = "Assignment";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr ll v_min = constraints::v_min, v_max = constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        input_file << n << "\n";
        std::vector<std::vector<ll>> cost(n, std::vector<ll>(n));
        for (usize i = 0; i < n; i++) { cost[i] = g_rng.uniform_int_vec(n, v_min, v_max); }
        for (usize i = 0; i < n; i++) {
            for (usize j = 0; j < n; j++) { input_file << cost[i][j] << " "; }
            input_file << "\n";
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n;
        input_file >> n;
        std::vector<std::vector<ll>> cost(n, std::vector<ll>(n));
        for (usize i = 0; i < n; i++) {
            for (usize j = 0; j < n; j++) { input_file >> cost[i][j]; }
        }
        std::vector<usize> ind(n);
        std::iota(ind.begin(), ind.end(), 0);
        ll min = std::numeric_limits<ll>::max();
        std::vector<usize> ans;
        do {
            ll sum = 0;
            for (usize i = 0; i < n; i++) { sum += cost[i][ind[i]]; }
            if (min > sum) { min = sum, ans = ind; }
        } while (std::next_permutation(ind.begin(), ind.end()));
        for (usize i = 0; i < n; i++) { output_file << ans[i] << " "; }
        output_file << "\n";
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize n;
        input_file >> n;
        std::vector<std::vector<ll>> cost(n, std::vector<ll>(n));
        for (usize i = 0; i < n; i++) {
            for (usize j = 0; j < n; j++) { input_file >> cost[i][j]; }
        }
        std::vector<usize> actual(n), output(n);
        for (usize i = 0; i < n; i++) {
            generated_output_file >> actual[i];
            solution_output_file >> output[i];
        }
        ll actual_cost = 0, output_cost = 0;
        for (usize i = 0; i < n; i++) {
            actual_cost += cost[i][actual[i]];
            output_cost += cost[i][output[i]];
        }
        return actual_cost == output_cost;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 8;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr ll v_min = -100000, v_max = 100000;
    };
};
}  // namespace libtest
