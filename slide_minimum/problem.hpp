#pragma once
#include <fstream>
#include <set>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct slide_minimum
{
    static constexpr const char* path       = "slide_minimum";
    static constexpr const char* name       = "Slide Minimum";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max);
        const auto k = rng.gen(1UL, n);
        pr.println(n, k);
        pr.println(rng.gen_vec(n, v_min, v_max));
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, k] = sc.read_vals<usize, usize>();
        const auto a      = sc.read_vec<ll>(n);
        std::vector<ll> min(n - k + 1);
        for (usize l = 0; l <= n - k; l++) {
            min[l] = std::accumulate(a.begin() + l, a.begin() + l + k, std::numeric_limits<ll>::max(), [](const ll a, const ll b) { return std::min(a, b); });
        }
        pr.println(min);
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto [n, k] = in_sc.read_vals<usize, usize>();
        const auto gen    = gen_sc.read_vec<ll>(n - k + 1);
        const auto sol    = sol_sc.may_read_vec<ll>(n - k + 1);
        for (usize i = 0; i < n - k + 1; i++) {
            if (gen[i] != sol[i]) { return false; }
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
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
    };
};
}  // namespace libtest
