#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct prime_factors
{
    static constexpr const char* path       = "prime_factors";
    static constexpr const char* name       = "Prime Factors";
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
        auto n = sc.read<usize>();
        std::vector<usize> ps, es;
        for (usize p = 2; p <= n; p++) {
            usize e = 0;
            while (n % p == 0) { n /= p, e++; }
            if (e > 0) { ps.push_back(p), es.push_back(e); }
        }
        pr.println(ps.size());
        for (usize i = 0; i < ps.size(); i++) { pr.println(ps[i], es[i]); }
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto gen_n = gen_sc.read<usize>();
        const auto sol_n = sol_sc.may_read<usize>();
        if (gen_n != sol_n) { return false; }
        for (usize i = 0; i < gen_n; i++) {
            const auto [gen_p, gen_e] = gen_sc.read_vals<usize, usize>();
            const auto [sol_p, sol_e] = sol_sc.may_read_vals<usize, usize>();
            if (gen_p != sol_p or gen_e != sol_e) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 2, n_max = 1000;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 2, n_max = 1000000;
    };
};
}  // namespace libtest
