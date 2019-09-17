#pragma once
#include <fstream>
#include <set>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct dynamic_sorted_array
{
    static constexpr const char* path       = "dynamic_sorted_array";
    static constexpr const char* name       = "Dynamic Sorted Array";
    static constexpr std::size_t time_limit = 5000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        printer pr{input_file};
        const auto q = rng.gen(q_min, q_max);
        pr.println(q);
        usize sz = 0;
        for (usize i = 0; i < q; i++) {
            const auto type = rng.gen(0, sz == 0 ? 2 : 3);
            if (type == 0) {
                pr.println(type, rng.gen(v_min, v_max)), sz++;
            } else if (type == 1) {
                pr.println(type, rng.gen(v_min, v_max));
            } else if (type == 2) {
                pr.println(type, rng.gen(v_min, v_max));
            } else {
                pr.println(type, rng.gen(0UL, sz - 1));
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto q = sc.read<usize>();
        std::multiset<ll> s;
        for (usize i = 0; i < q; i++) {
            const auto type = sc.read<usize>();
            if (type == 0) {
                const ll x = sc.read<ll>();
                s.insert(x);
            } else if (type == 1) {
                const ll x  = sc.read<ll>();
                usize index = 0;
                for (const auto v : s) {
                    if (v >= x) { break; }
                    index++;
                }
                pr.println(index);
            } else if (type == 2) {
                const ll x  = sc.read<ll>();
                usize index = 0;
                for (const auto v : s) {
                    if (v > x) { break; }
                    index++;
                }
                pr.println(index);
            } else {
                const usize i = sc.read<usize>();
                usize index   = 0;
                for (const auto v : s) {
                    if (index == i) {
                        pr.println(v);
                        break;
                    }
                    index++;
                }
            }
        }
    }
    static bool judge(std::ifstream& input_file, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner in_sc(input_file), gen_sc(generated_output_file), sol_sc(solution_output_file);
        const auto q = in_sc.read<usize>();
        for (usize i = 0; i < q; i++) {
            const auto type = in_sc.read<usize>();
            if (type == 0) {
                in_sc.read<ll>();
            } else if (type == 1) {
                in_sc.read<ll>();
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
            } else if (type == 2) {
                in_sc.read<ll>();
                if (gen_sc.read<usize>() != sol_sc.may_read<usize>()) { return false; }
            } else {
                in_sc.read<usize>();
                if (gen_sc.read<ll>() != sol_sc.may_read<ll>()) { return false; }
            }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize q_min = 2, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize q_min = 2, q_max = 100000;
        static constexpr ll v_min = -1000000000, v_max = 1000000000;
    };
};
}  // namespace libtest
