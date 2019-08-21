#pragma once
#include <fstream>
#include "../utils/random.hpp"
namespace libtest {
struct A_Plus_B  // なんでも良い
{
    static constexpr const char* PATH = "a_plus_b";  // libtestからの相対パス
    static constexpr const char* NAME = "A+B";       // 問題名
    static constexpr std::size_t TL = 100;           // 実行時間制限(ここでは100ms)

    /**
     * 必須となるstaticメンバ関数群
     *
     * generateInputSmall(std::ofstream& input_file) : 入力生成器(small)
     *   small入力input_fileに生成する関数
     * generateInputLarge(std::ofstream& input_file) : 入力生成器(large)
     *   large入力をinput_fileに生成する関数
     * generateOutputSmall(std::ifstream& input_file, std::ofstream& output_file) : 出力生成器(small)
     *   small入力ファイル input_fileから正しい出力をoutput_fileに生成する関数
     * validateOutput(std::ifstream& input_file, std::ifstream& output_file, std::ifstream& solution_output_file) : 出力検証器
     *   入力ファイルinput_file,
     *   正しい出力ファイルoutput_file,
     *   解法から生成された出力ファイルsolution_output_file からAC判定をする関数
     */
    static void generateInputSmall(std::ofstream& input_file) { input_file << rng.uniformInt(Small::AMIN, Small::AMAX) << " " << rng.uniformInt(Small::BMIN, Small::BMAX) << std::endl; }
    static void generateInputLarge(std::ofstream& input_file) { input_file << rng.uniformInt(Large::AMIN, Large::AMAX) << " " << rng.uniformInt(Large::BMIN, Large::BMAX) << std::endl; }
    static void generateOutputSmall(std::ifstream& input_file, std::ofstream& output_file)
    {
        int A, B;
        input_file >> A >> B;
        output_file << A + B << std::endl;
    }
    static bool validateOutput(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        int actual, output;
        generated_output_file >> actual;
        solution_output_file >> output;
        return actual == output;
    }

    /**
     * 制約を表す構造体(必須ではない)
     * generateInputSmall,generateOutputLargeの実装で使うと良い
     */
    struct Small
    {
        static constexpr int AMIN = 0, AMAX = 100;
        static constexpr int BMIN = 0, BMAX = 200;
    };
    struct Large
    {
        static constexpr int AMIN = 0, AMAX = 10000;
        static constexpr int BMIN = 0, BMAX = 20000;
    };
};
}  // namespace libtest
