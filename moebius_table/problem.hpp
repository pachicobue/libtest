#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct moebius_table
{
    static constexpr const char* path       = "moebius_table";
    static constexpr const char* name       = "Moebius Table";
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
        std::vector<int> vs(n + 1, -2);
        for (usize i = 1; i <= n; i++) {
            auto num = i;
            usize pn = 0;
            for (usize p = 2, e = 0; p <= i; p++, e = 0) {
                while (num % p == 0) { num /= p, e++; }
                if (e >= 2) { vs[i] = 0; }
                if (e >= 1) { pn++; }
            }
            vs[i] = (vs[i] == -2 ? pn % 2 == 0 ? 1 : -1 : 0);
        }
        pr.println(std::vector<int>(vs.begin() + 1, vs.end()));
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc(generated_output_file), sol_sc(solution_output_file);
        const usize n = in_sc.read<usize>();
        for (usize i = 0; i < n; i++) {
            if (gen_sc.read<int>() != sol_sc.may_read<int>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
    };
};
}  // namespace libtest
