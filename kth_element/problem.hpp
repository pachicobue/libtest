#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct kth_element
{
    static constexpr const char* path       = "kth_element";
    static constexpr const char* name       = "Kth Element";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max), q = rng.gen(q_min, q_max);
        pr.println(n, q);
        const auto v = rng.gen_vec(n, v_min, v_max);
        pr.println(v);
        for (usize i = 0; i < q; i++) {
            const auto p = rng.gen_pair(0UL, n - 1);
            const auto k = rng.gen(0UL, p.second - p.first);
            pr.println(p.first, p.second + 1, k);
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        const auto v      = sc.read_vec<ull>(n);
        for (usize i = 0; i < q; i++) {
            const auto [l, r, k] = sc.read_vals<usize, usize, usize>();
            auto u               = std::vector<ull>(v.begin() + l, v.begin() + r);
            std::nth_element(u.begin(), u.begin() + k, u.end());
            pr.println(u[k]);
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            const auto gen_c = gen_sc.read<ull>();
            const auto sol_c = sol_sc.may_read<ull>();
            if (gen_c != sol_c) { return false; }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ull v_min = 0, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ull v_min = 0, v_max = 10000000;
    };
};
}  // namespace libtest
