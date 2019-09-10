#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct count_palindromic_substring
{
    static constexpr const char* path       = "count_palindromic_substring";
    static constexpr const char* name       = "Count Palindromic Substring";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto c_min = constraints::c_min, c_max = constraints::c_max;
        printer pr{input_file};
        const auto n  = rng.gen(n_min, n_max);
        const auto m  = n / 2;
        const auto pv = rng.gen_vec(m, c_min, c_max);
        const auto p  = std::string(pv.begin(), pv.end());
        auto rp       = p;
        std::reverse(rp.begin(), rp.end());
        const auto s = p + std::string(n % 2, rng.gen(c_min, c_max)) + rp;
        pr.println(s);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto s  = sc.read<std::string>();
        const usize n = s.size();
        auto is_pal   = [&](const usize f, const usize l) {
            for (usize i = f; i < l; i++) {
                if (s[i] != s[f + l - i - 1]) { return false; }
            }
            return true;
        };
        ull ans = 0;
        for (usize i = 0; i < n; i++) {
            for (usize j = i + 1; j <= n; j++) {
                if (is_pal(i, j)) { ans++; }
            }
        }
        pr.println(ans);
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        return gen_sc.read<ull>() == sol_sc.may_read<ull>();
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr char c_min = 'a', c_max = 'z';
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr char c_min = 'a', c_max = 'z';
    };
};
}  // namespace libtest
