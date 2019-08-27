#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct rsq_ruq_large
{
    static constexpr const char* path       = "rsq_ruq_large";
    static constexpr const char* name       = "Range Sum Update Query (Large)";
    static constexpr std::size_t time_limit = 3000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto q = rng.gen(q_min, q_max);
        pr.println(q);
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0UL, 2UL);
            if (type == 0) {
                pr.println(type, rng.gen(n_min, n_max));
            } else if (type == 1) {
                pr.println(type, rng.gen(n_min, n_max), rng.gen(v_min, v_max));
            } else if (type == 2) {
                const auto p = rng.gen_pair(n_min, n_max);
                pr.println(type, p.first, p.second + 1);
            } else {
                const auto p = rng.gen_pair(n_min, n_max);
                pr.println(type, p.first, p.second + 1, rng.gen(v_min, v_max));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        constexpr auto n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        scanner sc(input_file);
        printer pr(output_file);
        const auto q = sc.read<usize>();
        std::vector<ll> vs(n_max - n_min + 1, 0);
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto ind = sc.read<usize>();
                pr.println(vs[ind - n_min]);
            } else if (type == 1) {
                const auto [ind, v] = sc.read_vals<usize, ll>();
                vs[ind - n_min]     = v;
            } else if (type == 2) {
                const auto [l, r] = sc.read_vals<usize, usize>();
                pr.println(std::accumulate(vs.begin() + l - n_min, vs.begin() + r - n_min, 0LL));
            } else {
                const auto [l, r, v] = sc.read_vals<usize, usize, ll>();
                for (usize i = l; i < r; i++) { vs[i - n_min] = v; }
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
                in_sc.read<usize>();
                if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
            } else if (type == 1) {
                in_sc.read_vals<usize, ll>();
            } else if (type == 2) {
                in_sc.read_vals<usize, usize>();
                if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
            } else {
                in_sc.read_vals<usize, usize, ll>();
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize n_min = 0, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 0, n_max = 10000000;
        static constexpr usize q_min = 1, q_max = 10000;
        static constexpr ll v_min = -10000, v_max = 10000;
    };
};
}  // namespace libtest
