#pragma once
#include <fstream>
#include <map>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct euler_trail
{
    static constexpr const char* path       = "euler_trail";
    static constexpr const char* name       = "Euler Trail";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto v_min = constraints::v_min, v_max = constraints::v_max;
        constexpr auto e_max = constraints::e_max;
        printer pr{input_file};
        const auto v = rng.gen(v_min, v_max);
        const auto e = rng.gen(v - 1, e_max);
        pr.println(v, e);
        using P = std::pair<usize, usize>;
        std::vector<P> edge;
        for (usize i = 0; i < v - 1; i++) { edge.push_back({i, i + 1}); }
        for (usize i = v - 1, p = v - 1; i < e; i++) {
            auto next = rng.gen(0UL, v - 2);
            if (next >= p) { next++; }
            edge.push_back({p, next}), p = next;
        }
        for (const auto& e : edge) { pr.println(e.first, e.second); }
    }
    static void generate_output(std::ifstream&, std::ofstream& output_file)
    {
        printer pr{output_file};
        pr.println("No Output");
    }
    static bool judge(std::ifstream& input_file, std::ifstream&, std::ifstream& solution_output_file)
    {
        scanner in_sc{input_file}, sol_sc{solution_output_file};
        const auto [v, e] = in_sc.read_vals<usize, usize>();
        using P           = std::pair<usize, usize>;
        std::map<P, int> mp;
        for (usize i = 0; i < e; i++) {
            const auto [u, v] = in_sc.read_vals<usize, usize>();
            mp[std::minmax(u, v)]++;
        }
        const auto sol_p = sol_sc.may_read<usize>();
        if (not sol_p) { return false; }
        for (usize i = 0, prev = *sol_p; i < e; i++) {
            const auto sol_p = sol_sc.may_read<usize>();
            if (not sol_p) { return false; }
            const auto p = *sol_p;
            if (mp[std::minmax(prev, p)] == 0) { return false; }
            mp[std::minmax(prev, p)]--, prev = p;
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_max = 200;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 1000;
        static constexpr usize e_max = 2000;
    };
};
}  // namespace libtest
