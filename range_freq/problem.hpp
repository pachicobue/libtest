#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct range_freq
{
    static constexpr const char* path       = "range_freq";
    static constexpr const char* name       = "Range Frequency";
    static constexpr std::size_t time_limit = 2000;
    static void generate_input_small(std::ofstream& input_file)
    {
        constexpr usize n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        constexpr usize q_min = small_constraints::q_min, q_max = small_constraints::q_max;
        constexpr ull v_min = small_constraints::v_min, v_max = small_constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max), q = g_rng.uniform_int(q_min, q_max);
        input_file << n << "\n";
        const auto v = g_rng.uniform_int_vec(n, v_min, v_max);
        for (const auto& e : v) { input_file << e << " "; }
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const auto p = g_rng.uniform_int_pair(0UL, n - 1);
            const auto v = g_rng.uniform_int_pair(v_min, v_max);
            input_file << p.first << " " << p.second + 1 << " " << v.first << " " << v.second + 1 << "\n";
        }
    }
    static void generate_input_large(std::ofstream& input_file)
    {
        constexpr usize n_min = large_constraints::n_min, n_max = large_constraints::n_max;
        constexpr usize q_min = large_constraints::q_min, q_max = large_constraints::q_max;
        constexpr ull v_min = large_constraints::v_min, v_max = large_constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max), q = g_rng.uniform_int(q_min, q_max);
        input_file << n << "\n";
        const auto v = g_rng.uniform_int_vec(n, v_min, v_max);
        for (const auto& e : v) { input_file << e << " "; }
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const auto p = g_rng.uniform_int_pair(0UL, n - 1);
            const auto v = g_rng.uniform_int_pair(v_min, v_max);
            input_file << p.first << " " << p.second + 1 << " " << v.first << " " << v.second + 1 << "\n";
        }
    }
    static void generate_output_small(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n, q;
        input_file >> n;
        std::vector<ull> v(n);
        for (auto& e : v) { input_file >> e; }
        input_file >> q;
        std::vector<usize> ans;
        for (usize i = 0; i < q; i++) {
            usize l, r;
            ull vmin, vsup;
            input_file >> l >> r >> vmin >> vsup;
            usize cnt = 0;
            for (usize i = l; i < r; i++) {
                if (vmin <= v[i] and v[i] < vsup) { cnt++; }
            }
            ans.push_back(cnt);
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
            ull actual, output;
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
