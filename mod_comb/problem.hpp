#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct mod_comb
{
    static constexpr const char* path       = "mod_comb";
    static constexpr const char* name       = "Modular combinatorial operations";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        const auto q = rng.gen(q_min, q_max);
        pr.println(n, q);
        for (usize i = 0; i < q; i++) {
            const usize type = rng.gen(0UL, 4UL);
            if (type == 0) {
                const auto i = rng.gen(1UL, n);
                pr.println(type, i);
            } else if (type == 1) {
                const auto i = rng.gen(0UL, n);
                pr.println(type, i);
            } else if (type == 2) {
                const auto i = rng.gen(1UL, n);
                pr.println(type, i);
            } else if (type == 3) {
                const auto p = rng.gen_pair(0UL, n);
                pr.println(type, p.first, p.second);
            } else {
                const auto p = rng.gen_pair(0UL, n);
                pr.println(type, p.first, p.second);
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        std::vector<std::vector<ll>> pas(n + 1, std::vector<ll>(n + 1, 0LL));
        pas[0][0] = 1 % mod;
        for (usize i = 1; i <= n; i++) {
            for (usize j = 0; j <= i; j++) { (pas[i][j] += pas[i - 1][j] + (j == 0 ? 0 : pas[i - 1][j - 1])) %= mod; }
        }
        auto p = [&](auto&& self, const ll x, const ll n) -> ll { return n == 0 ? 1LL : (n % 2 == 1) ? self(self, x, n - 1) * x % mod : self(self, x * x % mod, n / 2); };
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const auto i = sc.read<usize>();
                pr.println(p(p, i, mod - 2));
            } else if (type == 1) {
                const auto i = sc.read<usize>();
                ull ans      = 1;
                for (ull j = 1; j <= i; j++) { (ans *= j) %= mod; }
                pr.println(ans);
            } else if (type == 2) {
                const auto i = sc.read<usize>();
                ull ans      = 1;
                for (ull j = 1; j <= i; j++) { (ans *= p(p, j, mod - 2)) %= mod; }
                pr.println(ans);
            } else if (type == 3) {
                const auto [i, j] = sc.read_vals<usize, usize>();
                auto ans          = pas[i][j];
                for (ull j = 1; j <= i; j++) { (ans *= j) %= mod; }
                pr.println(ans);
            } else {
                const auto [i, j] = sc.read_vals<usize, usize>();
                pr.println(pas[i][j]);
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            if (gen_sc.read<uint>() != sol_sc.may_read<uint>()) { return false; }
        }
        return true;
    }
    static constexpr uint mod = 1000000007;
    struct small_constraints
    {
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr usize n_min = 1, n_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr usize n_min = 1, n_max = 100000;
    };
};
}  // namespace libtest
