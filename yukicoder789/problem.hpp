#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
// https://yukicoder.me/problems/no/789
struct yukicoder789
{
    static constexpr const char* path       = "yukicoder789";
    static constexpr const char* name       = "yukicoder 789";
    static constexpr std::size_t time_limit = 1000;
    using T                                 = ll;
    static void generate_input_small(std::ofstream&) {}
    static void generate_input_large(std::ofstream&) {}
    static void generate_output_small(std::ifstream&, std::ofstream&) {}
    static bool validate_output(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        T actual, output;
        generated_output_file >> actual, solution_output_file >> output;
        return actual == output;
    }
};
}  // namespace libtest
