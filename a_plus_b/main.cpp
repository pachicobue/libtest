#include "../utils/unittest.hpp"
#include "problem.hpp"
struct Solver
{
    static void solve(std::ifstream& input_file, std::ostream& solver_output_file)
    {
        while (true) {}
        int A, B;
        input_file >> A >> B;
        solver_output_file << A + B << std::endl;
    }
};
int main()
{
    using namespace libtest;
    UnitTest<A_Plus_B> unit_test{5, 5};
    unit_test.runTest<Solver>();
}
