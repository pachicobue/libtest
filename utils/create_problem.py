import os
import sys
import shutil
import textwrap

if __name__ == '__main__':
    args = sys.argv
    libtest_root = args[1]
    problem_relative_dir = args[2]
    problem_name = args[3]

    problem_absolute_dir = libtest_root + "/" + problem_relative_dir
    filename = "problem.hpp"
    problem_absolute_path = problem_absolute_dir + "/" + filename
    os.makedirs(problem_absolute_dir, exist_ok=True)

    contents_skeleton = textwrap.dedent('''\
    #pragma once
    #include <fstream>
    
    #include "../utils/printer.hpp"
    #include "../utils/random.hpp"
    #include "../utils/scanner.hpp"
    namespace libtest {{
    struct {0}
    {{
        static constexpr const char* path       = "{0}";
        static constexpr const char* name       = "{1}";
        static constexpr std::size_t time_limit = 2000;
        template<typename constraints>
        static void generate_input(std::ofstream& input_file)
        {{
            constexpr auto a_min = constraints::a_min, a_max = constraints::a_max;
            constexpr auto b_min = constraints::b_min, b_max = constraints::b_max;
            printer pr{{input_file}};
        }}
        static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
        {{
            scanner sc{{input_file}};
            printer pr{{output_file}};
        }}
        static bool judge(std::ifstream& input_file , std::ifstream& generated_output_file, std::ifstream& solution_output_file)
        {{
            scanner in_sc{{input_file}}, gen_sc{{generated_output_file}}, sol_sc{{solution_output_file}};
            return true;
        }}
        struct small_constraints
        {{
            static constexpr int a_min = 0, a_max = 100;
            static constexpr int b_min = 0, b_max = 200;
        }};
        struct large_constraints
        {{
            static constexpr int a_min = 0, a_max = 10000;
            static constexpr int b_min = 0, b_max = 20000;
        }};
    }};
    }}  // namespace libtest\
''')
    contents = contents_skeleton.format(problem_relative_dir, problem_name)

    # print(contents)
    output_file = open(problem_absolute_path, 'w')
    output_file.write(contents)
