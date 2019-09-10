#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct mod_operations
{
    static constexpr const char* path       = "mod_operations";
    static constexpr const char* name       = "Mod Operations";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto i_min = constraints::i_min, i_max = constraints::i_max;
        printer pr{input_file};
        auto x       = rng.gen(v_min, v_max);
        const auto q = rng.gen(q_min, q_max);
        pr.println(x, q);
        for (usize i = 0; i < q; i++) {
            const usize type = rng.gen(0UL, 13UL);
            if (type == 6 or type == 13) {
                const auto i = rng.gen(i_min, i_max);
                pr.println(type, i);
            } else {
                const auto v = rng.gen(v_min, v_max);
                pr.println(type, v);
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [xi, q] = sc.read_vals<ll, usize>();
        auto x             = xi % mod;
        for (usize i = 0; i < q; i++) {
            const auto [type, v] = sc.read_vals<usize, ll>();
            if (type == 0) {
                pr.println((x + v) % mod);
            } else if (type == 1) {
                pr.println((x - v) % mod);
            } else if (type == 2) {
                pr.println((x * v) % mod);
            } else if (type == 3) {
                pr.println(v % mod != 0, x);
            } else if (type == 4) {
                pr.println((v - x) % mod);
            } else if (type == 5) {
                pr.println(x % mod != 0, x);
            } else if (type == 6) {
                ll y = 1;
                for (ll i = 0; i < v; i++) { (y *= x) %= mod; }
                pr.println(y);
            } else if (type == 7) {
                pr.println((x - v) % mod == 0);
            } else if (type == 8) {
                x = v % mod;
            } else if (type == 9) {
                (x += v) %= mod;
            } else if (type == 10) {
                (x -= v) %= mod;
            } else if (type == 11) {
                (x *= v) %= mod;
            } else if (type == 12) {
                auto p = [&](auto&& self, const ll x, const ll n) -> ll { return n == 0 ? 1LL : (n % 2 == 1) ? self(self, x, n - 1) * x % mod : self(self, x * x % mod, n / 2); };
                (x *= p(p, v, mod - 2)) %= mod;
            } else {
                ll y = 1;
                for (ll i = 0; i < v; i++) { (y *= x) %= mod; }
                x = y;
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [x, q] = in_sc.read_vals<ll, usize>();
        for (usize i = 0; i < q; i++) {
            const auto [type, v] = in_sc.read_vals<usize, ll>();
            if (type <= 7) {
                if (type == 3) {
                    const auto [gen_b, gen_x] = gen_sc.read_vals<bool, ll>();
                    const auto [sol_b, sol_x] = sol_sc.may_read_vals<bool, ll>();
                    if (gen_b != sol_b) { return false; }
                    if (gen_b) {
                        if ((*sol_x * v - gen_x) % mod != 0) { return false; }
                    }
                } else if (type == 5) {
                    const auto [gen_b, gen_x] = gen_sc.read_vals<bool, ll>();
                    const auto [sol_b, sol_x] = sol_sc.may_read_vals<bool, ll>();
                    if (gen_b != sol_b) { return false; }
                    if (gen_b) {
                        if ((gen_x * *sol_x - v) % mod != 0) { return false; }
                    }
                } else {
                    const auto gen = gen_sc.read<ll>();
                    const auto sol = sol_sc.may_read<ll>();
                    if (not sol) { return false; }
                    if ((gen - *sol) % mod != 0) { return false; }
                }
            }
        }
        return true;
    }
    static constexpr uint mod = 1000000007;
    struct small_constraints
    {
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
        static constexpr ll i_min = 0, i_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize q_min = 1, q_max = 100000;
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
        static constexpr ll i_min = 0, i_max = 1000000000;
    };
};
}  // namespace libtest
