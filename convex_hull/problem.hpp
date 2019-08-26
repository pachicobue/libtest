#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct convex_hull
{
    static constexpr const char* path       = "convex_hull";
    static constexpr const char* name       = "Convex Hull";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize q_min = constraints::q_min, q_max = constraints::q_max;
        constexpr ll v_min = constraints::v_min, v_max = constraints::v_max;
        const usize q = g_rng.uniform_int(q_min, q_max);
        input_file << q << "\n";
        auto as = g_rng.uniform_int_vec(q, v_min, v_max), xs = g_rng.uniform_int_vec(q, v_min, v_max);
        std::sort(as.begin(), as.end(), std::greater<ll>{}), std::sort(xs.begin(), xs.end());
        usize an = 0, xn = 0;
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0, 1);
            if (type == 0) {
                input_file << "0 " << as[an++] << " " << g_rng.uniform_int(v_min, v_max) << "\n";
            } else {
                input_file << "1 " << xs[xn++] << "\n";
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize q;
        input_file >> q;
        using P = std::pair<ll, ll>;
        std::vector<P> ans;
        std::vector<ll> as, bs;
        for (usize i = 0; i < q; i++) {
            usize type;
            input_file >> type;
            if (type == 0) {
                ll a, b;
                input_file >> a >> b;
                as.push_back(a), bs.push_back(b);
            } else {
                ll x;
                input_file >> x;
                ll min = std::numeric_limits<ll>::max();
                for (usize i = 0; i < as.size(); i++) { min = std::min(min, as[i] * x + bs[i]); }
                ans.push_back({not as.empty(), min});
            }
        }
        output_file << ans.size() << "\n";
        for (const auto& e : ans) { output_file << e.first << " " << e.second << "\n"; }
    }
    static bool judge(std::ifstream& /*input_file*/, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize actual, output;
        generated_output_file >> actual, solution_output_file >> output;
        if (actual != output) { return false; }
        for (usize i = 0; i < actual; i++) {
            usize actual, output;
            generated_output_file >> actual, solution_output_file >> output;
            if (actual != output) { return false; }
        }
        return true;
    }
    struct small_constraints
    {
        static constexpr usize q_min = 1, q_max = 100;
        static constexpr ll v_min = -100, v_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize q_min = 1, q_max = 10000;
        static constexpr ll v_min = -100000, v_max = 100000;
    };
};
}  // namespace libtest
