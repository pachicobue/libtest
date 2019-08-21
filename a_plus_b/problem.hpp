#pragma once
#include <fstream>
#include "../utils/random.hpp"
namespace libtest {
struct A_Plus_B
{
    static constexpr const char* NAME = "a_plus_b";
    static constexpr std::size_t TL = 2000;
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

    static void generateInputSmall(std::ofstream& input_file) { input_file << rng.uniformInt(Small::AMIN, Small::AMAX) << " " << rng.uniformInt(Small::BMIN, Small::BMAX) << std::endl; }
    static void generateInputLarge(std::ofstream& input_file) { input_file << rng.uniformInt(Large::AMIN, Large::AMAX) << " " << rng.uniformInt(Large::BMIN, Large::BMAX) << std::endl; }
    static void generateOutputSmall(std::ifstream& input_file, std::ofstream& output_file)
    {
        int A, B;
        input_file >> A >> B;
        output_file << A + B << std::endl;
    }
    static bool validateOutputSmall(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solver_output_file)
    {
        int actual, output;
        generated_output_file >> actual;
        solver_output_file >> output;
        return actual == output;
    }
};
}  // namespace libtest
