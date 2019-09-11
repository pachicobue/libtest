#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct runtime_mod_combination
{
    static constexpr const char* path       = "runtime_mod_combination";
    static constexpr const char* name       = "Mod combinations (Runtime Mod)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto mod_max = constraints::mod_max;
        constexpr auto n       = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto mod = rng.gen_prime((uint)n + 1, mod_max);
        const auto q   = rng.gen(q_min, q_max);
        pr.println(mod, q);
        for (usize i = 0; i < q; i++) {
            const auto p = rng.gen_pair(0UL, n);
            if (rng.gen(0, 1)) {
                pr.println(p.first, p.second);
            } else {
                pr.println(p.second, p.first);
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        constexpr auto n    = small_constraints::n_max;
        const auto [mod, q] = sc.read_vals<ull, usize>();
        std::vector<std::vector<ll>> pas(n + 1, std::vector<ll>(n + 1, 0LL));
        pas[0][0] = 1 % mod;
        for (usize i = 1; i <= n; i++) {
            for (usize j = 0; j <= i; j++) { (pas[i][j] += pas[i - 1][j] + (j == 0 ? 0 : pas[i - 1][j - 1])) %= mod; }
        }
        for (usize i = 0; i < q; i++) {
            const auto [n, k] = sc.read_vals<usize, usize>();
            pr.println(pas[n][k]);
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [mod, q] = in_sc.read_vals<ull, usize>();
        for (usize i = 0; i < q; i++) {
            if (gen_sc.read<uint>() != sol_sc.may_read<uint>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr uint mod_max = 1000;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr usize n_min = 1, n_max = 100;
    };
    struct large_constraints
    {
        static constexpr uint mod_max = 1000000000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr usize n_min = 1, n_max = 100000;
    };
};  // namespace libtest
}  // namespace libtest
