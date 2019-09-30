#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct xor_maximization
{
    static constexpr const char* path       = "xor_maximization";
    static constexpr const char* name       = "Xor Maximization";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto d_max = constraints::d_max;
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto v_max = 1ULL << d_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        const auto v = rng.gen_vec(n, 0ULL, v_max);
        pr.println(n);
        pr.println(v);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto n         = sc.read<usize>();
        const auto v         = sc.read_vec<ll>(n);
        constexpr auto v_max = 1UL << small_constraints::d_max;
        std::vector<bool> dp(v_max, false);
        dp[0] = true;
        for (usize i = 0; i < n; i++) {
            auto tmp = dp;
            for (usize j = 0; j < v_max; j++) {
                if (not dp[j]) { continue; }
                tmp[j ^ v[i]] = true;
            }
            dp = tmp;
        }
        for (usize i = 0; i < v_max; i++) {
            if (dp[v_max - i - 1]) {
                pr.println(v_max - i - 1);
                break;
            }
        }
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        return gen_sc.read<ull>() == sol_sc.may_read<ull>();
    }
    struct small_constraints
    {
        static constexpr usize d_max = 10;
        static constexpr usize n_min = 1, n_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize d_max = 60;
        static constexpr usize n_min = 1, n_max = 1000;
    };
};
}  // namespace libtest
