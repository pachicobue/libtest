#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct a_divide_b_large
{
    using bigint                            = boost::multiprecision::cpp_int;
    static constexpr const char* path       = "a_divide_b_large";
    static constexpr const char* name       = "A/B (Large)";
    static constexpr std::size_t time_limit = 1000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto d_min = constraints::d_min, d_max = constraints::d_max;
        printer pr{input_file};
        std::string n[2];
        for (usize i = 0; i < 2; i++) {
            const auto d = rng.gen(d_min, d_max);
            if (rng.gen(0, 1) == 1) { n[i].push_back('-'); }
            for (usize j = 0; j < d; j++) {
                n[i].push_back(rng.gen(j == 0 ? '1' : '0', '9'));
            }
        }
        pr.println(n[0], n[1]);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [a, b] = sc.read_vals<bigint, bigint>();
        pr.println(a / b);
    }
    static bool judge(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc(generated_output_file), sol_sc(solution_output_file);
        return gen_sc.read<std::string>() == sol_sc.may_read<std::string>();
    }
    struct small_constraints
    {
        static constexpr usize d_min = 1, d_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize d_min = 1, d_max = 3000;
    };
};
}  // namespace libtest
