#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct ruq
{
    static constexpr const char* path       = "ruq";
    static constexpr const char* name       = "Range Update Query";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        const auto q = rng.gen(q_min, q_max);
        pr.println(n, q);
        const auto vs = rng.gen_vec(n, v_min, v_max);
        pr.println(vs);
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0UL, 3UL);
            if (type == 0) {
                pr.println(type, rng.gen(0UL, n - 1));
            } else if (type == 1) {
                pr.println(type, rng.gen(0UL, n - 1), rng.gen(v_min, v_max));
            } else {
                const auto p = rng.gen_pair(0Ul, n - 1);
                pr.println(type, p.first, p.second + 1, rng.gen(v_min, v_max));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        auto vs           = sc.read_vec<ll>(n);
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto ind = sc.read<usize>();
                pr.println(vs[ind]);
            } else if (type == 1) {
                const auto [ind, v] = sc.read_vals<usize, ll>();
                vs[ind]             = v;
            } else {
                const auto [l, r, v] = sc.read_vals<usize, usize, ll>();
                for (usize i = l; i < r; i++) { vs[i] = v; }
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            const auto type = in_sc.read<usize>();
            if (type == 0) {
                in_sc.read<usize>();
                if (gen_sc.read<ll>() != sol_sc.safe_read<ll>()) { return false; }
            } else if (type == 1) {
                in_sc.read_vals<usize, ll>();
            } else {
                in_sc.read_vals<usize, usize, ll>();
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
    };
};
}  // namespace libtest
