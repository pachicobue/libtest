#pragma once
#include <fstream>
#include <queue>

#include "../utils/graph.hpp"
#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct biconnected_components
{
    static constexpr const char* path       = "biconnected_components";
    static constexpr const char* name       = "BiConnected Components";
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
        const auto g = random_graph(v, e, true);
        for (usize i = 0; i < v; i++) {
            for (const usize to : g.edge[i]) {
                if (i < to) { pr.println(i, to); }
            }
        }
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
        std::vector<P> edge(e);
        for (usize i = 0; i < e; i++) {
            const auto [u, v] = in_sc.read_vals<usize, usize>();
            edge[i]           = {u, v};
        }
        std::vector<std::vector<bool>> ok(v, std::vector<bool>(v, true));
        for (usize i = 0; i < e; i++) {
            unionfind uf(v);
            for (usize j = 0; j < e; j++) {
                if (i == j) { continue; }
                const auto [u, v] = edge[j];
                uf.unite(u, v);
            }
            for (usize j = 0; j < v; j++) {
                for (usize k = 0; k < v; k++) { ok[j][k] = ok[j][k] and uf.same(j, k); }
            }
        }
        const auto comp = sol_sc.may_read_vec<usize>(v);
        for (usize i = 0; i < v; i++) {
            if (not comp[i]) { return false; }
        }
        for (usize i = 0; i < v; i++) {
            for (usize j = i + 1; j < v; j++) {
                if (*comp[i] == *comp[j]) {
                    if (not ok[i][j] or not ok[j][i]) { return false; }
                } else {
                    if (ok[i][j] and ok[j][i]) { return false; }
                }
            }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize v_min = 2, v_max = 100;
        static constexpr usize e_max = 110;
    };
    struct large_constraints
    {
        static constexpr usize v_min = 2, v_max = 1000;
        static constexpr usize e_max = 1020;
    };
};
}  // namespace libtest
