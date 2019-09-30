#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct pattern_matching_multiple
{
    static constexpr const char* path       = "pattern_matching_multiple";
    static constexpr const char* name       = "Pattern Matching (Multiple Pattern)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        printer pr{input_file};
        pr.println("a");
        pr.println(1);
        pr.println("a");
    }
    static void generate_output(std::ifstream&, std::ofstream& output_file)
    {
        printer pr{output_file};
        pr.println(1, 0);
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto [s, n] = in_sc.read_vals<std::string, usize>();
        for (usize i = 0; i < n; i++) {
            const auto gen_n = gen_sc.read<usize>();
            const auto sol_n = sol_sc.may_read<usize>();
            if (gen_n != sol_n) { return false; }
            for (usize i = 0; i < gen_n; i++) {
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
            }
        }
        return true;
    }
    struct small_constraints
    {};
    struct large_constraints
    {};
};
}  // namespace libtest
