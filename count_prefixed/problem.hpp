#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct count_prefixed
{
    static constexpr const char* path       = "count_prefixed";
    static constexpr const char* name       = "Count Prefixed String";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto l_max = constraints::l_max;
        constexpr auto c_min = constraints::c_min, c_max = constraints::c_max;
        printer pr{input_file};
        const auto q = rng.gen(q_min, q_max);
        pr.println(q);
        auto l = rng.gen(q * 3, l_max);
        std::vector<std::string> s(q);
        for (usize i = 0; i < q / 2; i++) {
            const usize n = rng.gen(1UL, 3UL);
            l -= n;
            for (usize j = 0; j < n; j++) { s[i].push_back(rng.gen(c_min, c_max)); }
        }
        for (usize i = q / 2; i < q; i++) { s[i].push_back(rng.gen(c_min, c_max)), l--; }
        for (usize i = 0; i < l; i++) {
            const usize p = rng.gen(q / 2, q - 1);
            s[p].push_back(rng.gen(c_min, c_max));
        }
        std::shuffle(s.begin(), s.end(), rng);
        for (usize i = 0; i < q; i++) {
            const usize type = rng.gen(0, 1);
            pr.println(type, s[i]);
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const usize q = sc.read<usize>();
        std::vector<std::string> S;
        for (usize i = 0; i < q; i++) {
            const auto [type, s] = sc.read_vals<usize, std::string>();
            if (type == 0) {
                S.push_back(s);
            } else {
                usize ans = 0;
                for (const auto& t : S) {
                    if (s.size() > t.size()) { continue; }
                    if (t.substr(0, s.size()) == s) { ans++; }
                }
                pr.println(ans);
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const usize q = in_sc.read<usize>();
        for (usize i = 0; i < q; i++) {
            const auto [type, s] = in_sc.read_vals<usize, std::string>();
            if (type == 1) {
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
            }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr usize l_max = 1000;
        static constexpr char c_min = 'a', c_max = 'b';
    };
    struct large_constraints
    {
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr usize l_max = 400000;
        static constexpr char c_min = 'f', c_max = 'h';
    };
};
}  // namespace libtest
