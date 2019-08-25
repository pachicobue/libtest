#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct segments
{
    static constexpr const char* path       = "segments";
    static constexpr const char* name       = "Segments Decomposition";
    static constexpr std::size_t time_limit = 2000;
    static void generate_input_small(std::ofstream& input_file)
    {
        constexpr usize n_min = small_constraints::n_min, n_max = small_constraints::n_max;
        constexpr usize q_min = small_constraints::q_min, q_max = small_constraints::q_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const usize q = g_rng.uniform_int(q_min, q_max);
        usize sz      = 1;
        for (; sz < n; sz <<= 1) {}
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                const auto p = g_rng.uniform_int_pair(0UL, n - 1);
                input_file << "0 " << p.first << " " << p.second + 1 << "\n";
            } else if (type == 1) {
                input_file << "1 " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else {
                input_file << "2 " << g_rng.uniform_int(1UL, sz * 2 - 1) << "\n";
            }
        }
    }
    static void generate_input_large(std::ofstream& input_file)
    {
        constexpr usize n_min = large_constraints::n_min, n_max = large_constraints::n_max;
        constexpr usize q_min = large_constraints::q_min, q_max = large_constraints::q_max;
        const usize n = g_rng.uniform_int(n_min, n_max);
        const usize q = g_rng.uniform_int(q_min, q_max);
        usize sz      = 1;
        for (; sz < n; sz <<= 1) {}
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                const auto p = g_rng.uniform_int_pair(0UL, n - 1);
                input_file << "0 " << p.first << " " << p.second + 1 << "\n";
            } else if (type == 1) {
                input_file << "1 " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else {
                input_file << "2 " << g_rng.uniform_int(1UL, sz * 2 - 1) << "\n";
            }
        }
    }
    static void generate_output_small(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n, q;
        input_file >> n >> q;
        usize sz = 1, lg = 0;
        for (; sz < n; sz <<= 1, lg++) {}
        using P = std::pair<usize, usize>;
        std::vector<P> rs{{0, 0}};
        for (usize base = sz; base != 0; base >>= 1) {
            for (usize l = 0; l < sz; l += base) { rs.push_back({l, l + base}); }
        }
        std::vector<std::vector<usize>> ans;
        for (usize i = 0; i < q; i++) {
            usize type;
            input_file >> type;
            if (type == 0) {
                std::vector<bool> on(sz, false);
                usize l, r;
                input_file >> l >> r;
                std::vector<usize> sub;
                for (usize i = l; i < r; i++) { on[i] = true; }
                for (usize i = 1; i < rs.size(); i++) {
                    const usize left = rs[i].first, right = rs[i].second;
                    bool con = true;
                    for (usize j = left; j < right; j++) { con &= on[j]; }
                    if (con) {
                        sub.push_back(i);
                        for (usize j = left; j < right; j++) { on[j] = false; }
                    }
                }
                ans.push_back(sub);
            } else if (type == 1) {
                usize ind;
                input_file >> ind;
                std::vector<usize> sub;
                for (usize i = 1; i < rs.size(); i++) {
                    const usize left = rs[i].first, right = rs[i].second;
                    if (left <= ind and ind < right) { sub.push_back(i); }
                }
                ans.push_back(sub);
            } else {
                usize ind;
                input_file >> ind;
                ans.push_back(std::vector<usize>{rs[ind].first, rs[ind].second});
            }
        }
        output_file << ans.size() << "\n";
        for (const auto& v : ans) {
            output_file << v.size() << " ";
            for (const auto p : v) { output_file << p << " "; }
            output_file << "\n";
        }
    }
    static bool validate_output(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize q_actual, q_output;
        generated_output_file >> q_actual;
        solution_output_file >> q_output;
        if (q_actual != q_output) { return false; }
        for (usize i = 0; i < q_actual; i++) {
            usize m_actual, m_output;
            generated_output_file >> m_actual;
            solution_output_file >> m_output;
            if (m_actual != m_output) { return false; }
            std::vector<uint> actual, output;
            for (usize i = 0; i < m_actual; i++) {
                uint a, o;
                generated_output_file >> a;
                solution_output_file >> o;
                actual.push_back(a), output.push_back(o);
            }
            std::sort(actual.begin(), actual.end()), std::sort(output.begin(), output.end());
            for (usize i = 0; i < m_actual; i++) {
                if (actual[i] != output[i]) { return false; }
            }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
    };
};
}  // namespace libtest
