#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct runtime_mod_convolution
{
    static constexpr const char* path       = "runtime_mod_convolution";
    static constexpr const char* name       = "Mod Convolution (Runtime Mod)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto mod_min = constraints::mod_min, mod_max = constraints::mod_max;
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        printer pr{input_file};
        const auto n   = rng.gen(n_min, n_max);
        const auto m   = rng.gen(n_min, n_max);
        const auto mod = rng.gen_prime(mod_min, mod_max);
        pr.println(mod, n, m);
        const auto a = rng.gen_vec(n, 0U, mod - 1);
        const auto b = rng.gen_vec(m, 0U, mod - 1);
        pr.println(a);
        pr.println(b);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [mod, n, m] = sc.read_vals<uint, usize, usize>();
        const auto a = sc.read_vec<ll>(n), b = sc.read_vec<ll>(m);
        std::vector<uint> ans(n + m - 1, 0);
        for (usize i = 0; i < n; i++) {
            for (usize j = 0; j < m; j++) { (ans[i + j] += static_cast<uint>(a[i] * b[j] % mod)) %= mod; }
        }
        pr.println(ans);
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [mod, n, m] = in_sc.read_vals<uint, usize, usize>();
        for (usize i = 0; i < m + n - 1; i++) {
            if (gen_sc.read<uint>() != sol_sc.may_read<uint>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr uint mod_min = 2, mod_max = 1000;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr uint mod_min = 2, mod_max = 1000000000;
    };
};
}  // namespace libtest
