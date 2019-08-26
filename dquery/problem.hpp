#pragma once
#include <fstream>
#include <set>

#include "../utils/random.hpp"
namespace libtest {
struct dquery
{
    static constexpr const char* path       = "dquery";
    static constexpr const char* name       = "D-query";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr usize q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr ll v_min = constraints::v_min, v_max = constraints::v_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        input_file << n << "\n";
        const auto a = g_rng.uniform_int_vec(n, v_min, v_max);
        for (const auto& e : a) { input_file << e << " "; }
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << "\n"
                   << q << "\n";
        for (usize i = 0; i < q; i++) {
            const auto p = g_rng.uniform_int_pair(0UL, n - 1);
            input_file << p.first << " " << p.second + 1 << "\n";
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n, q;
        input_file >> n;
        std::vector<ull> a(n);
        for (auto& e : a) { input_file >> e; }
        input_file >> q;
        output_file << q << "\n";
        for (usize i = 0; i < q; i++) {
            usize l, r;
            input_file >> l >> r;
            std::set<ull> st;
            for (usize i = l; i < r; i++) { st.insert(a[i]); }
            output_file << st.size() << "\n";
        }
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
        static constexpr usize n_min = 1, n_max = 10000;
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ull v_min = 0, v_max = 999;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 10000;
        static constexpr usize q_min = 1, q_max = 10000;
        static constexpr ull v_min = 0, v_max = 99999;
    };
};
}  // namespace libtest
