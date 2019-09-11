#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct runtime_mod_fibonacci
{
    static constexpr const char* path       = "runtime_mod_fibonacci";
    static constexpr const char* name       = "Mod Fibonacci (Runtime Mod)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto mod_min = constraints::mod_min, mod_max = constraints::mod_max;
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto k_min = constraints::k_min, k_max = constraints::k_max;
        printer pr{input_file};
        const auto n   = rng.gen(n_min, n_max);
        const auto k   = rng.gen(k_min, k_max);
        const auto mod = rng.gen_prime(mod_min, mod_max);
        pr.println(n, k, mod);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [n, k, mod] = sc.read_vals<usize, usize, uint>();
        std::vector<uint> ans(n + 1, 1);
        for (usize i = k; i <= n; i++) {
            ans[i] = 0;
            for (usize j = i - k; j < i; j++) { (ans[i] += ans[j]) %= mod; }
        }
        pr.println(ans[n]);
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        return gen_sc.read<uint>() == sol_sc.may_read<uint>();
    }
    struct small_constraints
    {
        static constexpr uint mod_min = 2, mod_max = 10000;
        static constexpr uint n_min = 1, n_max = 100;
        static constexpr uint k_min = 1, k_max = 10;
    };
    struct large_constraints
    {
        static constexpr uint mod_min = 2, mod_max = 1000000000;
        static constexpr uint n_min = 1, n_max = 10000;
        static constexpr uint k_min = 1, k_max = 10;
    };
};
}  // namespace libtest
