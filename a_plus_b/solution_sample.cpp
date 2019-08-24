/**
 * 解法テストのサンプル
 *
 * 本来はlibtestにはproblem.hppのような問題だけ置き、solutionはライブラリ側で実装する
 * ライブラリを用いて解法を実装、テストする方法を例示する
 */
#include <cassert>

#include "../utils/logger.hpp"
#include "../utils/unit_test.hpp"
#include "problem.hpp"
namespace {
struct ac
{
    static constexpr const char* name = "AC";  // 解法名
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        int a, b;
        input_file >> a >> b;
        solution_output_file << a + b << std::endl;
    }
};
struct wa
{
    static constexpr const char* name = "WA";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        int a, b;
        input_file >> a >> b;
        solution_output_file << a + b + 1 << std::endl;
    }
};
struct tle_soft
{
    static constexpr const char* name = "Soft TLE";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        std::this_thread::sleep_for(std::chrono::milliseconds{a_plus_b::time_limit + 50});
        int a, b;
        input_file >> a >> b;
        solution_output_file << a + b << std::endl;
    }
};
struct tle_hard
{
    static constexpr const char* name = "Heavy TLE";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        while (true) {}
        int a, b;
        input_file >> a >> b;
        solution_output_file << a + b << std::endl;
    }
};
}  // namespace
int main()
{
    libtest::unit_test<libtest::a_plus_b> test{5, 5};  // smallを5ケース, largeを5ケース生成
    test.run_test<ac>();
    test.run_test<wa>();
    test.run_test<tle_soft>();
    test.run_test<tle_hard>();
}
