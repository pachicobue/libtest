#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct segment_decomposition
{
    static constexpr const char* path       = "segment_decomposition";
    static constexpr const char* name       = "Segment Decomposition";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto l_min = constraints::l_min, l_max = constraints::l_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto n = 1UL << rng.gen(l_min, l_max);
        const auto q = rng.gen(q_min, q_max);
        usize sz     = 1;
        for (; sz < n; sz <<= 1) {}
        pr.println(n, q);
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0UL, 1UL);
            if (type == 0) {
                const auto p = rng.gen_pair(0UL, n - 1);
                pr.println(type, p.first, p.second + 1);
            } else {
                pr.println(type, rng.gen(0UL, n - 1));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        usize sz = 1, lg = 0;
        for (; sz < n; sz <<= 1, lg++) {}
        using P = std::pair<usize, usize>;
        std::vector<P> rs{{0, 0}};
        for (usize base = sz; base != 0; base >>= 1) {
            for (usize l = 0; l < sz; l += base) { rs.push_back({l, l + base}); }
        }
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto [l, r] = sc.read_vals<usize, usize>();
                std::vector<bool> on(sz, false);
                std::fill(on.begin() + l, on.begin() + r, true);
                std::vector<usize> sub;
                for (usize i = 1; i < rs.size(); i++) {
                    const usize left = rs[i].first, right = rs[i].second;
                    bool con = true;
                    for (usize j = left; j < right; j++) { con &= on[j]; }
                    if (con) {
                        sub.push_back(i);
                        for (usize j = left; j < right; j++) { on[j] = false; }
                    }
                }
                pr.println(sub.size());
                for (const usize i : sub) { pr.println(rs[i].first, rs[i].second); }
            } else {
                const auto ind = sc.read<usize>();
                std::vector<usize> sub;
                for (usize i = 1; i < rs.size(); i++) {
                    const usize left = rs[i].first, right = rs[i].second;
                    if (left <= ind and ind < right) { sub.push_back(i); }
                }
                pr.println(sub.size());
                for (const usize i : sub) { pr.println(rs[i].first, rs[i].second); }
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
                in_sc.read_vals<usize, usize>();
                const auto gen_m = gen_sc.read<usize>();
                const auto sol_m = sol_sc.may_read<usize>();
                if (gen_m != sol_m) { return false; }
                for (usize i = 0; i < gen_m; i++) {
                    const auto [gen_l, gen_r] = gen_sc.read_vals<usize, usize>();
                    const auto [sol_l, sol_r] = sol_sc.may_read_vals<usize, usize>();
                    if (gen_l != sol_l or gen_r != sol_r) { return false; }
                }
            } else {
                in_sc.read_vals<usize>();
                const auto gen_m = gen_sc.read<usize>();
                const auto sol_m = sol_sc.may_read<usize>();
                if (gen_m != sol_m) { return false; }
                for (usize i = 0; i < gen_m; i++) {
                    const auto [gen_l, gen_r] = gen_sc.read_vals<usize, usize>();
                    const auto [sol_l, sol_r] = sol_sc.may_read_vals<usize, usize>();
                    if (gen_l != sol_l or gen_r != sol_r) { return false; }
                }
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize l_min = 0, l_max = 7;
        static constexpr usize q_min = 1, q_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize l_min = 0, l_max = 16;
        static constexpr usize q_min = 1, q_max = 100000;
    };
};
}  // namespace libtest
