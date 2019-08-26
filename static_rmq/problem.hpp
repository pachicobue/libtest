#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct static_rmq
{
    static constexpr const char* path       = "static_rmq";
    static constexpr const char* name       = "Static Range Minimum Query";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr usize q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr ll v_min = constraints::v_min, v_max = constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const auto vs = g_rng.uniform_int_vec(n, v_min, v_max);
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << n << "\n";
        for (usize i = 0; i < n; i++) { input_file << vs[i] << " "; }
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const auto p = g_rng.uniform_int_pair(0UL, n - 1);
            input_file << p.first << " " << p.second + 1 << "\n";
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n;
        input_file >> n;
        std::vector<ll> vs(n);
        for (auto& e : vs) { input_file >> e; }
        usize q;
        input_file >> q;
        std::vector<ll> ans;
        for (usize i = 0; i < q; i++) {
            usize l, r;
            input_file >> l >> r;
            ll min = std::numeric_limits<ll>::max();
            for (usize i = l; i < r; i++) { min = std::min(min, vs[i]); }
            ans.push_back(min);
        }
        output_file << ans.size() << "\n";
        for (const auto e : ans) { output_file << e << "\n"; }
    }
    static bool judge(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize q_actual, q_output;
        generated_output_file >> q_actual;
        solution_output_file >> q_output;
        if (q_actual != q_output) { return false; }
        for (usize i = 0; i < q_actual; i++) {
            ll actual, output;
            generated_output_file >> actual;
            solution_output_file >> output;
            if (actual != output) { return false; }
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
