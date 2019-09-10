#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct divisors
{
    static constexpr const char* path       = "divisors";
    static constexpr const char* name       = "Divisors";
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
        const auto n = sc.read<ll>();
        std::vector<ll> ds;
        for (ll i = 1; i <= n; i++) {
            if (n % i == 0) { ds.push_back(i); }
        }
        pr.println(ds.size());
        pr.println(ds);
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto gen_n = gen_sc.read<usize>();
        const auto sol_n = sol_sc.may_read<usize>();
        if (gen_n != sol_n) { return false; }
        for (usize i = 1; i <= gen_n; i++) {
            if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr ll n_min = 1, n_max = 1000;
    };
    struct large_constraints
    {
        static constexpr ll n_min = 1, n_max = 10000000000;
    };
};
}  // namespace libtest
