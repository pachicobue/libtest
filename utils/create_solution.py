import os
import sys
import shutil
import textwrap

if __name__ == '__main__':
    args = sys.argv
    test_root = args[1]
    solution_name = args[2]

    problem_absolute_path = test_root + "/" + problem_name + ".hpp"
    contents_skeleton = textwrap.dedent('''\
#include "libtest/{0}/problem.hpp"
#include "libtest/utils/printer.hpp"
#include "libtest/utils/scanner.hpp"
#include "libtest/utils/unit_test.hpp"
#include "problem.hpp"
namespace {{
struct solution
{{
    static constexpr const char* name = "{0}";
    static void solve(std::ifstream& input_file, std::ostream& solution_output_file)
    {{
        libtest::scanner sc{{input_file}};
        libtest::printer pr{{solution_output_file}};
    }}
}};
}}  // namespace
int main()
{{
    libtest::unit_test<libtest::solution> test{{5, 5}}.run_test<solution>();
}}
''')
    contents = contents_skeleton.format(solution_name)

    output_file = open(problem_absolute_path, 'w')
    output_file.write(contents)
