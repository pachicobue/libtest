#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct unionfind
{
    static constexpr const char* path       = "unionfind";
    static constexpr const char* name       = "Union Find Tree";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        printer pr{input_file};
        const auto n = rng.gen(n_min, n_max), q = rng.gen(q_min, q_max);
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = rng.gen(0UL, 2UL);
            if (type == 0) {
                pr.println(type, rng.gen(0UL, n - 1), rng.gen(0UL, n - 1));
            } else if (type == 1) {
                pr.println(type, rng.gen(0UL, n - 1), rng.gen(0UL, n - 1));
            } else {
                pr.println(type, rng.gen(0UL, n - 1));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [n, q] = sc.read_vals<usize, usize>();
        std::vector<usize> id(n);
        std::iota(id.begin(), id.end(), 0);
        for (usize i = 0; i < q; i++) {
            const usize type = sc.read<usize>();
            if (type == 0) {
                const auto [a, b] = sc.read_vals<usize, usize>();
                if (id[a] != id[b]) {
                    const usize aid = id[a], bid = id[b];
                    for (usize i = 0; i < n; i++) {
                        if (id[i] == bid) { id[i] = aid; }
                    }
                }
            } else if (type == 1) {
                const auto [a, b] = sc.read_vals<usize, usize>();
                pr.println(id[a] == id[b]);
            } else {
                const auto ind = sc.read<usize>();
                usize sum      = 0;
                for (usize i = 0; i < n; i++) {
                    if (id[i] == id[ind]) { sum++; }
                }
                pr.println(sum);
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file);
        scanner gen_sc(generated_output_file);
        scanner sol_sc(solution_output_file);
        const auto [n, q] = in_sc.read_vals<usize, usize>();
        for (usize i = 0; i < q; i++) {
            const usize type = in_sc.read<usize>();
            if (type == 0) {
                in_sc.read_vals<usize, usize>();
            } else if (type == 1) {
                in_sc.read_vals<usize, usize>();
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
            } else {
                in_sc.read<usize>();
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
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
