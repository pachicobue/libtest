#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct raq
{
    static constexpr const char* path       = "raq";
    static constexpr const char* name       = "Range Add Query";
    static constexpr std::size_t time_limit = 2000;
    using T                                 = ll;
    static void generate_input_small(std::ofstream& input_file)
    {
        constexpr usize n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        constexpr usize q_min = small_constraints::q_min, q_max = small_constraints::q_max;
        constexpr T v_min = small_constraints::v_min, v_max = small_constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const auto vs = g_rng.uniform_int_vec(n, v_min, v_max);
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << n << "\n";
        for (usize i = 0; i < n; i++) { input_file << vs[i] << " "; }
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                input_file << "0 " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else {
                const auto p = g_rng.uniform_int_pair(0UL, n - 1);
                input_file << "1 " << p.first << " " << p.second + 1 << " " << g_rng.uniform_int(v_min, v_max) << "\n";
            }
        }
    }
    static void generate_input_large(std::ofstream& input_file)
    {
        constexpr usize n_min = large_constraints::n_min, n_max = large_constraints::n_max;
        constexpr usize q_min = large_constraints::q_min, q_max = large_constraints::q_max;
        constexpr T v_min = large_constraints::v_min, v_max = large_constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const auto vs = g_rng.uniform_int_vec(n, v_min, v_max);
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << n << "\n";
        for (usize i = 0; i < n; i++) { input_file << vs[i] << " "; }
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                input_file << "0 " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else {
                const auto p = g_rng.uniform_int_pair(0UL, n - 1);
                input_file << "1 " << p.first << " " << p.second + 1 << " " << g_rng.uniform_int(v_min, v_max) << "\n";
            }
        }
    }
    static void generate_output_small(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n;
        input_file >> n;
        std::vector<T> vs(n);
        for (auto& e : vs) { input_file >> e; }
        usize q;
        input_file >> q;
        std::vector<T> ans;
        for (usize i = 0; i < q; i++) {
            usize type;
            input_file >> type;
            if (type == 0) {
                usize i;
                input_file >> i;
                ans.push_back(vs[i]);
            } else {
                usize l, r;
                T v;
                input_file >> l >> r >> v;
                for (usize i = l; i < r; i++) { vs[i] += v; }
            }
        }
        output_file << ans.size() << "\n";
        for (const auto e : ans) { output_file << e << "\n"; }
    }
    static bool validate_output(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize q_actual, q_output;
        generated_output_file >> q_actual;
        solution_output_file >> q_output;
        if (q_actual != q_output) { return false; }
        for (usize i = 0; i < q_actual; i++) {
            T actual, output;
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
        static constexpr int v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr T v_min = -1000000000, v_max = 1000000000;
    };
};
}  // namespace libtest