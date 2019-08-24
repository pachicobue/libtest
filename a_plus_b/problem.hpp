#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct a_plus_b  // なんでも良い
{
    static constexpr const char* path       = "a_plus_b";  // libtestからの相対パス
    static constexpr const char* name       = "A+B";       // 問題名
    static constexpr std::size_t time_limit = 100;         // 実行時間制限(ここでは100ms)
    /**
     * 必須となるstaticメンバ関数群
     *
     * generate_input_small(std::ofstream& input_file) : 入力生成器(small)
     *   small入力input_fileに生成する関数
     * generate_input_large(std::ofstream& input_file) : 入力生成器(large)
     *   large入力をinput_fileに生成する関数
     * generate_output_small(std::ifstream& input_file, std::ofstream& output_file) : 出力生成器(small)
     *   small入力ファイル input_fileから正しい出力をoutput_fileに生成する関数
     * validate_output(std::ifstream& input_file, std::ifstream& output_file, std::ifstream& solution_output_file) : 出力検証器
     *   入力ファイルinput_file,
     *   正しい出力ファイルoutput_file,
     *   解法から生成された出力ファイルsolution_output_file からAC判定をする関数
     */
    static void generate_input_small(std::ofstream& input_file) { input_file << g_rng.uniform_int(small_constranits::a_min, small_constranits::a_max) << " " << g_rng.uniform_int(small_constranits::b_min, small_constranits::b_max) << std::endl; }
    static void generate_input_large(std::ofstream& input_file) { input_file << g_rng.uniform_int(large_constraints::a_min, large_constraints::a_max) << " " << g_rng.uniform_int(large_constraints::b_min, large_constraints::b_max) << std::endl; }
    static void generate_output_small(std::ifstream& input_file, std::ofstream& output_file)
    {
        int a, b;
        input_file >> a >> b;

        output_file << a + b << std::endl;
    }
    static bool validate_output(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        int actual, output;
        generated_output_file >> actual;
        solution_output_file >> output;
        return actual == output;
    }

    /**
     * 制約を表す構造体(必須ではない)
     * generate_input_small,generate_output_largeの実装で使うと良い
     */
    struct small_constranits
    {
        static constexpr int a_min = 0, a_max = 100;
        static constexpr int b_min = 0, b_max = 200;
    };
    struct large_constraints
    {
        static constexpr int a_min = 0, a_max = 10000;
        static constexpr int b_min = 0, b_max = 20000;
    };
};
}  // namespace libtest
