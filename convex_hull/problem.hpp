#pragma once
#include <fstream>

#include "../utils/inf.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct convex_hull
{
    static constexpr const char* path       = "convex_hull";
    static constexpr const char* name       = "Convex Hull (Lowest Envelope)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const usize q = rng.gen(q_min, q_max);
        pr.println(q);
        auto as = rng.gen_vec(q, v_min, v_max), xs = rng.gen_vec(q, v_min, v_max);
        std::sort(as.begin(), as.end(), std::greater<ll>{}), std::sort(xs.begin(), xs.end());
        usize an = 0, xn = 0;
        for (usize i = 0; i < q; i++) {
            const usize type = rng.gen(0, 1);
            if (type == 0) {
                pr.println(0, as[an++], rng.gen(v_min, v_max));
            } else {
                pr.println(1, xs[xn++]);
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto q = sc.read<usize>();
        std::vector<ll> as, bs;
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto [a, b] = sc.read_vals<usize, usize>();
                as.push_back(a), bs.push_back(b);
            } else {
                const auto x = sc.read<ll>();
                ll min       = inf<ll>;
                for (usize i = 0; i < as.size(); i++) { min = std::min(min, as[i] * x + bs[i]); }
                pr.println(min);
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
                in_sc.read_vals<usize, usize>();
            } else {
                in_sc.read<ll>();
                const auto gen_y = gen_sc.read<ll>();
                const auto sol_y = sol_sc.may_read<ll>();
                if (gen_y > large_constraints::v_max * large_constraints::v_max + large_constraints::v_max) {
                    if (sol_y <= large_constraints::v_max * large_constraints::v_max + large_constraints::v_max) { return false; }
                } else {
                    if (gen_y != sol_y) { return false; }
                }
            }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ll v_min = -100000, v_max = 100000;
    };
};
}  // namespace libtest
