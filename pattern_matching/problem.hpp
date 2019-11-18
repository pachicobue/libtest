#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct pattern_matching
{
    static constexpr const char* path       = "pattern_matching";
    static constexpr const char* name       = "Pattern Matching";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto m_min = constraints::m_min, m_max = constraints::m_max;
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto c_min = constraints::c_min, c_max = constraints::c_max;
        printer pr{input_file};
        const auto m  = rng.gen(m_min, m_max);
        const auto n  = rng.gen(n_min, n_max);
        const auto pv = rng.gen_vec(n, c_min, c_max);
        const auto p  = std::string(pv.begin(), pv.end());
        std::string s;
        for (; s.size() < m;) {
            if (s.size() + n > m) {
                for (; s.size() < m;) { s.push_back(rng.gen(c_min, c_max)); }
            } else {
                if (rng.gen(0, 1)) {
                    s += p;
                } else {
                    s.push_back(rng.gen(c_min, c_max));
                }
            }
        }
        pr.println(s);
        pr.println(p);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [s, p] = sc.read_vals<std::string, std::string>();
        const usize m = s.size(), n = p.size();
        std::vector<usize> ans;
        for (usize i = 0; i + n <= m; i++) {
            if (s.substr(i, n) == p) { ans.push_back(i); }
        }
        pr.println(ans.size());
        pr.println(ans);
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto gen_n = gen_sc.read<usize>();
        const auto sol_n = sol_sc.may_read<usize>();
        if (gen_n != sol_n) { return false; }
        for (usize i = 0; i < gen_n; i++) {
            if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize m_min = 1, m_max = 100;
        static constexpr usize n_min = 1, n_max = 3;
        static constexpr char c_min = 'a', c_max = 'z';
    };
    struct large_constraints
    {
        static constexpr usize m_min = 1, m_max = 1000000;
        static constexpr usize n_min = 1, n_max = 10000;
        static constexpr char c_min = 'a', c_max = 'z';
    };
};
}  // namespace libtest
