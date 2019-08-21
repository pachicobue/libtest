/**
 * 解法テストのサンプル
 *
 * 本来はlibtestにはproblem.hppのような問題だけ置き、solutionはライブラリ側で実装する
 * ライブラリを用いて解法を実装、テストする方法を例示する
 */
#include "../utils/logger.hpp"
#include "../utils/unittest.hpp"
#include "problem.hpp"
namespace {
struct AC
{
    static constexpr const char* NAME = "AC";  // 解法名
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        int A, B;
        input_file >> A >> B;
        solution_output_file << A + B << std::endl;
    }
};
struct WA
{
    static constexpr const char* NAME = "WA";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        int A, B;
        input_file >> A >> B;
        solution_output_file << A + B + 1 << std::endl;
    }
};
struct TLE_1
{
    static constexpr const char* NAME = "Soft TLE";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        std::this_thread::sleep_for(std::chrono::milliseconds{A_Plus_B::TL + 50});
        int A, B;
        input_file >> A >> B;
        solution_output_file << A + B << std::endl;
    }
};
struct TLE_2
{
    static constexpr const char* NAME = "Heavy TLE";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {
        using namespace libtest;
        while (true) {}
        int A, B;
        input_file >> A >> B;
        solution_output_file << A + B << std::endl;
    }
};
}  // namespace
int main()
{
    libtest::UnitTest<libtest::A_Plus_B> unit_test{5, 5};  // smallを5ケース, largeを5ケース生成
    unit_test.runTest<AC>();
    unit_test.runTest<WA>();
    unit_test.runTest<TLE_1>();
    unit_test.runTest<TLE_2>();
}
