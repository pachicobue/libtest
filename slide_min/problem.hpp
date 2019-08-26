#pragma once
#include <fstream>
#include <set>

#include "../utils/random.hpp"
namespace libtest {
struct slide_min
{
    static constexpr const char* path       = "slide_min";
    static constexpr const char* name       = "Slide Minimum";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr ll v_min = constraints::v_min, v_max = constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const usize k = g_rng.uniform_int(1UL, n);
        input_file << n << " " << k << "\n";
        const auto a = g_rng.uniform_int_vec(n, v_min, v_max);
        for (const auto& e : a) { input_file << e << " "; }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n, k;
        input_file >> n >> k;
        std::vector<ll> a(n);
        for (auto& e : a) { input_file >> e; }
        output_file << n << "\n";
        for (usize r = 1; r < k; r++) {
            ll min = std::numeric_limits<ll>::max();
            for (usize i = 0; i < r; i++) { min = std::min(min, a[i]); }
            output_file << min << " ";
        }
        for (usize l = 0; l <= n - k; l++) {
            ll min = std::numeric_limits<ll>::max();
            for (usize i = l; i < l + k; i++) { min = std::min(min, a[i]); }
            output_file << min << " ";
        }
        output_file << "\n";
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize actual, output;
        generated_output_file >> actual, solution_output_file >> output;
        if (actual != output) { return false; }
        for (usize i = 0; i < actual; i++) {
            usize actual, output;
            generated_output_file >> actual, solution_output_file >> output;
            if (actual != output) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ll v_min = -100000, v_max = 100000;
    };
};
}  // namespace libtest
