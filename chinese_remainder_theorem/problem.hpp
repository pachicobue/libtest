#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct chinese_remainder_theorem
{
    static constexpr const char* path       = "chinese_remainder_theorem";
    static constexpr const char* name       = "Chinese Remainder Theorem";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto mod_min = constraints::mod_min, mod_max = constraints::mod_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        pr.println(n);
        const auto v  = rng.gen(v_min, v_max);
        const auto ms = rng.gen_vec(n, mod_min, mod_max);
        for (usize i = 0; i < n; i++) { pr.println(v % ms[i], ms[i]); }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto n = sc.read<usize>();
        std::vector<ll> vs(n), ms(n);
        for (usize i = 0; i < n; i++) { std::tie(vs[i], ms[i]) = sc.read_vals<ll, ll>(); }
        for (ll v = small_constraints::v_min; v <= small_constraints::v_max; v++) {
            bool ok = true;
            for (usize i = 0; i < n; i++) {
                if (v % ms[i] != vs[i]) { ok = false; }
            }
            if (ok) {
                pr.println(v);
                break;
            }
        }
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc(generated_output_file), sol_sc(solution_output_file);
        return gen_sc.read<ll>() == sol_sc.may_read<ll>();
    }
    struct small_constraints
    {
        static constexpr usize n_min = 2, n_max = 5;
        static constexpr ll mod_min = 1, mod_max = 10;
        static constexpr ll v_min = 0, v_max = 100000LL;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 2, n_max = 2;
        static constexpr ll mod_min = 1, mod_max = 100000;
        static constexpr ll v_min = 0, v_max = 1000000000000000LL;
    };
};
}  // namespace libtest
