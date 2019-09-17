#pragma once
#include <cassert>
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct rsq_2d
{
    static constexpr const char* path       = "rsq_2d";
    static constexpr const char* name       = "Range Sum Query (2D)";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto h_min = constraints::h_min, h_max = constraints::h_max;
        constexpr auto w_min = constraints::w_min, w_max = constraints::w_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto h = rng.gen(h_min, h_max);
        const auto w = rng.gen(w_min, w_max);
        const auto q = rng.gen(q_min, q_max);
        pr.println(h, w, q);
        const auto vs = rng.gen_vec(h, w, v_min, v_max);
        for (const auto& v : vs) { pr.println(v); }
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0UL, 1UL);
            if (type == 0) {
                pr.println(type, rng.gen(0UL, h - 1), rng.gen(0UL, w - 1), rng.gen(v_min, v_max));
            } else {
                const auto hp = rng.gen_pair(0Ul, h - 1);
                const auto wp = rng.gen_pair(0Ul, w - 1);
                pr.println(type, hp.first, hp.second + 1, wp.first, wp.second + 1);
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [h, w, q] = sc.read_vals<usize, usize, usize>();
        auto vs              = sc.read_vec<ll>(h, w);
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto [h, w, v] = sc.read_vals<usize, usize, ll>();
                vs[h][w]             = v;
            } else {
                const auto [hl, hr, wl, wr] = sc.read_vals<usize, usize, usize, usize>();
                ll ans                      = 0;
                for (usize h = hl; h < hr; h++) {
                    for (usize w = wl; w < wr; w++) { ans += vs[h][w]; }
                }
                pr.println(ans);
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [h, w, q] = in_sc.read_vals<usize, usize, usize>();
        const auto vs        = in_sc.read_vec<ll>(h, w);
        for (usize i = 0; i < q; i++) {
            const auto type = in_sc.read<usize>();
            if (type == 0) {
                in_sc.read_vals<usize, usize, ll>();
            } else {
                in_sc.read_vals<usize, usize, usize, usize>();
                if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize h_min = 1, h_max = 100;
        static constexpr usize w_min = 1, w_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize h_min = 1, h_max = 1000;
        static constexpr usize w_min = 1, w_max = 1000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
    };
};
}  // namespace libtest
