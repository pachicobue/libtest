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
        std::vector<bool> isp(n + 1, true);
        isp[0] = isp[1] = false;
        for (usize i = 2; i <= n; i++) {
            for (usize j = 2; j * j <= i; j++) {
                if (i % j == 0) { isp[i] = false; }
            }
        }
        pr.println(std::vector<bool>(isp.begin() + 1, isp.end()));
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 1; i <= n; i++) {
            if (gen_sc.read<bool>() != sol_sc.may_read<bool>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 1000;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 1000000;
    };
};
}  // namespace libtest
