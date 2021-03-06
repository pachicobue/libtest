#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct static_rmq
{
    static constexpr const char* path       = "static_rmq";
    static constexpr const char* name       = "Range Minimum Query (Static)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n  = rng.gen(n_min, n_max);
        const auto q  = rng.gen(q_min, q_max);
        const auto vs = rng.gen_vec(n, v_min, v_max);
        pr.println(n, q);
        pr.println(vs);
        for (usize i = 0; i < q; i++) {
            const auto p = rng.gen_pair(0UL, n - 1);
            pr.println(p.first, p.second + 1);
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        const auto vs     = sc.read_vec<ll>(n);
        for (usize i = 0; i < q; i++) {
            const auto [l, r] = sc.read_vals<usize, usize>();
            pr.println(std::accumulate(vs.begin() + l, vs.begin() + r, std::numeric_limits<ll>::max(), [](const ll a, const ll b) { return std::min(a, b); }));
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
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
