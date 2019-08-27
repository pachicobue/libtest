#pragma once
#include <fstream>

#include "../utils/printer.hpp"
#include "../utils/random.hpp"
#include "../utils/scanner.hpp"
namespace libtest {
struct a_plus_b  // なんでも良い
{
    static constexpr const char* path       = "a_plus_b";  // libtestからの相対パス
    static constexpr const char* name       = "A+B";       // 問題名
    static constexpr std::size_t time_limit = 100;         // 実行時間制限(ここでは100ms)
    /**
     * 必須となるstaticメンバ関数群
     *
     * generate_input<Constraints>(std::ofstream& input_file) : 入力生成器
     *   制約構造体constraintsから入力を生成する関数
     * generate_output(std::ifstream& input_file, std::ofstream& output_file) : 出力生成器
     *   入力ファイル(small) input_fileから正しい出力をoutput_fileに生成する関数
     * judge(std::ifstream& input_file, std::ifstream& output_file, std::ifstream& solution_output_file) : 出力検証器
     *   入力ファイルinput_file,
     *   正しい出力ファイルoutput_file,
     *   解法から生成された出力ファイルsolution_output_file からAC判定をする関数
     */
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr auto a_min = constraints::a_min, a_max = constraints::a_max;
        constexpr auto b_min = constraints::b_min, b_max = constraints::b_max;
        printer pr{input_file};
        pr.println(rng.gen(a_min, a_max), rng.gen(b_min, b_max));
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        scanner sc(input_file);
        printer pr(output_file);
        const auto [a, b] = sc.read_vals<int, int>();
        pr.println(a + b);
    }
    static bool judge(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        scanner gen_sc(generated_output_file), sol_sc(solution_output_file);
        return gen_sc.read<int>() == sol_sc.may_read<int>();
    }
    /**
     * 制約を表す構造体
     * generate_inputの実装で使う
     */
    struct small_constraints
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
