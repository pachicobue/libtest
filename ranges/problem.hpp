#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct ranges
{
    static constexpr const char* path       = "ranges";
    static constexpr const char* name       = "Disjoint Ranges";
    static constexpr std::size_t time_limit = 2000;
    static void generate_input_small(std::ofstream& input_file)
    {
        constexpr ll n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        constexpr usize q_min = small_constraints::q_min, q_max = small_constraints::q_max;
        const ll n    = g_rng.uniform_int(n_min, n_max) + 1;
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                const auto p = g_rng.uniform_int_pair(n_min, n_max);
                input_file << "0 " << p.first << " " << p.second + 1 << "\n";
            } else if (type == 1) {
                const auto p = g_rng.uniform_int_pair(n_min, n_max);
                input_file << "1 " << p.first << " " << p.second + 1 << "\n";
            } else {
                input_file << "2 " << g_rng.uniform_int(n_min, n_max) << "\n";
            }
        }
    }
    static void generate_input_large(std::ofstream& input_file)
    {
        constexpr ll n_min = large_constraints::n_min, n_max = large_constraints::n_max;
        constexpr usize q_min = large_constraints::q_min, q_max = large_constraints::q_max;
        const ll n    = g_rng.uniform_int(n_min, n_max) + 1;
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                const auto p = g_rng.uniform_int_pair(n_min, n_max);
                input_file << "0 " << p.first << " " << p.second + 1 << "\n";
            } else if (type == 1) {
                const auto p = g_rng.uniform_int_pair(n_min, n_max);
                input_file << "1 " << p.first << " " << p.second + 1 << "\n";
            } else {
                input_file << "2 " << g_rng.uniform_int(n_min, n_max) << "\n";
            }
        }
    }
    static void generate_output_small(std::ifstream& input_file, std::ofstream& output_file)
    {
        constexpr ll n_min = large_constraints::n_min, n_max = large_constraints::n_max;
        ll n;
        usize q;
        input_file >> n >> q;
        std::vector<bool> on(n_max - n_min + 2, false);
        using P  = std::pair<ll, ll>;
        using PP = std::pair<bool, P>;
        std::vector<PP> ans;
        for (usize i = 0; i < q; i++) {
            usize type;
            input_file >> type;
            if (type == 0) {
                ll a, b;
                input_file >> a >> b, a -= (n_min - 1), b -= (n_min - 1);
                for (ll i = a; i < b; i++) { on[i] = true; }
            } else if (type == 1) {
                ll a, b;
                input_file >> a >> b, a -= (n_min - 1), b -= (n_min - 1);
                for (ll i = a; i < b; i++) { on[i] = false; }
            } else {
                ll ind;
                input_file >> ind, ind -= (n_min - 1);
                ll l = ind, r = ind;
                for (; on[l]; l--) {}
                for (; on[r]; r++) {}
                ans.push_back({on[ind], {l + n_min, r + n_min - 1}});
            }
        }
        output_file << ans.size() << "\n";
        for (const auto& e : ans) { output_file << e.first << " " << e.second.first << " " << e.second.second << "\n"; }
    }
    static bool validate_output(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize q_actual, q_output;
        generated_output_file >> q_actual;
        solution_output_file >> q_output;
        if (q_actual != q_output) { return false; }
        for (usize i = 0; i < q_actual; i++) {
            bool actual_on, output_on;
            ll actual_left, actual_right, output_left, output_right;
            generated_output_file >> actual_on >> actual_left >> actual_right;
            solution_output_file >> output_on >> output_left >> output_right;
            if (actual_on != output_on) { return false; }
            if (actual_on and (actual_left != output_left or actual_right != output_right)) { return false; }
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
