#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct maximum_prime_factor_table
{
    static constexpr const char* path       = "maximum_prime_factor_table";
    static constexpr const char* name       = "Maximum Prime Factor Table";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        pr.println(n);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto n = sc.read<usize>();
        std::vector<usize> ans(n + 1, 0);
        for (usize i = 2; i <= n; i++) {
            usize num = i;
            for (usize p = 2; p <= num; p++) {
                if (num % p != 0) { continue; }
                ans[i] = std::max(ans[i], p);
                while (num % p == 0) { num /= p; }
            }
        }
        pr.println(std::vector<usize>(ans.begin() + 2, ans.end()));
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 2; i <= n; i++) {
            if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 2, n_max = 1000;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 2, n_max = 100000;
    };
};
}  // namespace libtest
