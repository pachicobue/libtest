#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct xor_convolution
{
    static constexpr const char* path       = "xor_convolution";
    static constexpr const char* name       = "Xor-Convolution";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto m_min = constraints::m_min, m_max = constraints::m_max;
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto m = rng.gen(m_min, m_max), n = rng.gen(n_min, n_max);
        const auto a = rng.gen_vec(m, v_min, v_max), b = rng.gen_vec(n, v_min, v_max);
        pr.println(m, n);
        pr.println(a);
        pr.println(b);
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc{input_file};
        printer pr{output_file};
        const auto [m, n] = sc.read_vals<usize, usize>();
        const auto a = sc.read_vec<ll>(m), b = sc.read_vec<ll>(n);
        usize sz = 1;
        for (; sz < m or sz < n; sz <<= 1) {}
        std::vector<ll> ans(sz, 0);
        for (usize i = 0; i < m; i++) {
            for (usize j = 0; j < n; j++) { ans[i ^ j] += a[i] * b[j]; }
        }
        pr.println(ans);
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, gen_sc{generated_output_file}, sol_sc{solution_output_file};
        const auto [m, n] = in_sc.read_vals<usize, usize>();
        usize sz          = 1;
        for (; sz < m or sz < n; sz <<= 1) {}
        for (usize i = 0; i < sz; i++) {
            if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize m_min = 1, m_max = 100;
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize m_min = 1, m_max = 100000;
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr ll v_min = -1000000, v_max = 1000000;
    };
};
}  // namespace libtest
