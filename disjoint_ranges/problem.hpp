#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct disjoint_ranges
{
    static constexpr const char* path       = "disjoint_ranges";
    static constexpr const char* name       = "Disjoint Ranges";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto q = rng.gen(q_min, q_max);
        pr.println(q);
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0UL, 2UL);
            if (type == 0) {
                const auto p = rng.gen_pair(n_min, n_max);
                pr.println(type, p.first, p.second + 1);
            } else if (type == 1) {
                const auto p = rng.gen_pair(n_min, n_max);
                pr.println(type, p.first, p.second + 1);
            } else {
                pr.println(type, rng.gen(n_min, n_max));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        constexpr ll n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        scanner sc(input_file);
        printer pr(output_file);
        const auto q = sc.read<usize>();
        std::vector<bool> on(n_max - n_min + 3, false);
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto [a, b] = sc.read_vals<ll, ll>();
                for (ll i = a; i < b; i++) { on[i - (n_min - 1)] = true; }
            } else if (type == 1) {
                const auto [a, b] = sc.read_vals<ll, ll>();
                for (ll i = a; i < b; i++) { on[i - (n_min - 1)] = false; }
            } else {
                const auto ind = sc.read<ll>();
                if (on[ind - (n_min - 1)]) {
                    ll l = ind, r = ind;
                    for (; on[l - (n_min - 1)]; l--) {}
                    for (; on[r - (n_min - 1)]; r++) {}
                    pr.println(on[ind - (n_min - 1)], l + 1, r);
                } else {
                    pr.println(on[ind - (n_min - 1)], 0, 0);
                }
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto q = in_sc.read<usize>();
        for (usize i = 0; i < q; i++) {
            const auto type = in_sc.read<usize>();
            if (type == 0) {
                in_sc.read_vals<ll, ll>();
            } else if (type == 1) {
                in_sc.read_vals<ll, ll>();
            } else {
                in_sc.read<ll>();
                const auto [gen_b, gen_l, gen_r] = gen_sc.read_vals<bool, ll, ll>();
                const auto [sol_b, sol_l, sol_r] = sol_sc.may_read_vals<bool, ll, ll>();
                if (gen_b != sol_b) { return false; }
                if (gen_b) {
                    if (gen_l != sol_l or gen_r != sol_r) { return false; }
                }
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr ll n_min = -100, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
    };
    struct large_constraints
    {
        static constexpr ll n_min = -10000000, n_max = 10000000;
        static constexpr usize q_min = 1, q_max = 100000;
    };
};
}  // namespace libtest
