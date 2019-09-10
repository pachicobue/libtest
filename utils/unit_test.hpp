#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <sstream>

#include "printer.hpp"
#include "types.hpp"
namespace libtest {
namespace fs = std::filesystem;
template<typename Problem>
class unit_test
{
    using color = typename ansi_sgr::color;
    using attr  = typename ansi_sgr::attribute;

public:
    static constexpr ansi_sgr base_color{color::cyan, attr::reset};
    static constexpr ansi_sgr message_color{color::white, attr::reset};
    static constexpr ansi_sgr bold_message_color{color::white, attr::bold};
    static constexpr ansi_sgr ac_color{color::green, attr::reset};
    static constexpr ansi_sgr wa_color{color::red, attr::reset};
    static constexpr ansi_sgr tle_color{color::red, attr::reset};
    static constexpr ansi_sgr passed_color{color::green, attr::bold};
    static constexpr ansi_sgr failed_color{color::red, attr::bold};
    static constexpr ansi_sgr fatal_color{color::red, attr::reset};
    static constexpr ansi_sgr bold_fatal_color{color::red, attr::bold};
    static constexpr ansi_sgr reset{color::white, attr::reset};
    unit_test() = delete;
    template<typename Solution>
    static bool run_test(const usize small_gen_num, const usize large_gen_num, const bool testcase_cache = false)
    {
        cprintf(base_color, "[==========] "), cprintf(bold_message_color, "Start (problem=\"%\",solution=\"%\")\n", Problem::name, Solution::name);
        gen(small_gen_num, large_gen_num, testcase_cache);
        const auto result  = test<Solution>(small_gen_num, large_gen_num);
        const usize passed = result.first, failed = result.second;
        cprintf(base_color, "[----------] "), cprintf(bold_message_color, "Summarize results\n");
        if (passed > 0) { cprintf(passed_color, "[  PASSED  ] "), cprintf(message_color, "% cases\n", passed); }
        if (failed > 0) { cprintf(passed_color, "[  FAILED  ] "), cprintf(message_color, "% cases\n", failed); }
        cprintf(base_color, "[==========] "), cprintf(bold_message_color, "End (problem=\"%\",solution=\"%\")\n\n", Problem::name, Solution::name);
        return failed == 0;
    }

private:
    static fs::path test_case_dir() { return fs::path(LIBTEST_ROOT) / std::string(Problem::path) / "test_cases"; }
    static fs::path gen_case_dir() { return test_case_dir() / "generated"; }
    static fs::path small_genfile_path(const usize index, const bool in) { return gen_case_dir() / (std::string("small_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    static fs::path large_genfile_path(const usize index, const bool in) { return gen_case_dir() / (std::string("large_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    template<typename Process>
    static usize run(const Process& process)
    {
        std::promise<usize> promise;
        std::future<usize> future = promise.get_future();
        const auto start          = std::chrono::high_resolution_clock::now();
        std::thread thread(
            [&](std::promise<usize> promise) {
                process();
                const auto end      = std::chrono::high_resolution_clock::now();
                const usize time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                promise.set_value(time_ms);
            },
            std::move(promise));
        if (future.wait_for(std::chrono::milliseconds{Problem::time_limit * 2}) != std::future_status::timeout) {
            const usize time_ms = future.get();
            return thread.join(), time_ms;
        } else {
            return thread.detach(), Problem::time_limit * 2;  // 直後にstd::terminate()する
        }
    }
    static void gen(const usize small_gen_num, const usize large_gen_num, const bool testcase_cache)
    {
        cprintf(base_color, "[----------] "), cprintf(bold_message_color, "Generate tests\n");
        static std::ofstream input_file;
        static std::ifstream output_file;
        fs::create_directory(test_case_dir()), fs::create_directory(gen_case_dir());
        for (usize index = 1; index <= small_gen_num; index++) {
            const fs::path input_file_path = small_genfile_path(index, true), output_file_path = small_genfile_path(index, false);
            if (testcase_cache and fs::exists(input_file_path)) { continue; }
            cprintf(ac_color, "[ GENERATE ] "), cprintln(message_color, input_file_path.filename());
            input_file.open(input_file_path);
            Problem::template generate_input<typename Problem::small_constraints>(input_file);
            input_file.close(), output_file.open(input_file_path), input_file.open(output_file_path);
            cprintf(ac_color, "[ GENERATE ] "), cprintln(message_color, output_file_path.filename());
            Problem::generate_output(output_file, input_file);
            input_file.close(), output_file.close();
        }
        for (usize index = 1; index <= large_gen_num; index++) {
            const fs::path input_file_path = large_genfile_path(index, true);
            if (testcase_cache and fs::exists(input_file_path)) { continue; }
            cprintf(ac_color, "[ GENERATE ] "), cprintln(message_color, input_file_path.filename());
            input_file.open(input_file_path);
            Problem::template generate_input<typename Problem::large_constraints>(input_file);
            input_file.close();
        }
    }
    template<typename Solution>
    static bool check(const fs::path& input_file_path)
    {
        static std::ifstream input_file, generated_output_file, solution_output_file_in;
        static std::ofstream solution_output_file;
        cprintf(ac_color, "[ RUN      ] "), cprintln(message_color, input_file_path.filename());
        auto solution_out_path = input_file_path;
        solution_out_path.replace_extension(".txt");
        input_file.open(input_file_path), solution_output_file.open(solution_out_path);
        const usize time_ms = run([&]() { Solution::solve(input_file, solution_output_file); });
        input_file.close(), solution_output_file.close();
        bool passed = false;
        if (time_ms == Problem::time_limit * 2) {
            cprintf(bold_fatal_color, "[ TIME OUT ] "), cprintf(fatal_color, "Did not end in time_limit*2 (time_limit=% ms)\n", Problem::time_limit);
            cprintf(fatal_color, "[==========] "), cprintf(bold_fatal_color, "Abort (problem=\"%\",solution=\"%\")\n", Problem::name, Solution::name);
            std::terminate();
        } else if (time_ms >= Problem::time_limit) {
            cprintf(tle_color, "[      TLE ] "), cprintf(message_color, "% (% ms)\n", input_file_path.filename(), time_ms);
        } else {
            auto generated_out_path = input_file_path;
            generated_out_path.replace_extension(".out");
            if (fs::exists(generated_out_path)) {
                input_file.open(input_file_path), generated_output_file.open(generated_out_path), solution_output_file_in.open(solution_out_path);
                const bool ok = Problem::judge(input_file, generated_output_file, solution_output_file_in);
                if (not ok) {
                    cprintf(wa_color, "[       WA ] "), cprintf(message_color, "% (% ms)\n", input_file_path.filename(), time_ms);
                    std::ifstream in_file{input_file_path}, gen_file{generated_out_path}, sol_file{solution_out_path};
                    std::string line;
                    cprintln(message_color, "(Input)");
                    while (std::getline(in_file, line)) { cprintln(message_color, line); }
                    cprintln(message_color, "(Expected)");
                    while (std::getline(gen_file, line)) { cprintln(message_color, line); }
                    cprintln(message_color, "(Output)");
                    while (std::getline(sol_file, line)) { cprintln(message_color, line); }
                } else {
                    cprintf(ac_color, "[       AC ] "), cprintf(message_color, "% (% ms)\n", input_file_path.filename(), time_ms);
                    passed = true;
                }
                solution_output_file_in.close();
            } else {
                cprintf(ac_color, "[       OK ] "), cprintf(message_color, "% (% ms)\n", input_file_path.filename(), time_ms);
                passed = true;
            }
        }
        generated_output_file.close(), input_file.close(), solution_output_file.close();
        return passed;
    }
    template<typename Solution>
    static std::pair<usize, usize> test(const usize small_gen_num, const usize large_gen_num)
    {
        cprintf(base_color, "[----------] "), cprintf(bold_message_color, "Run tests\n");
        std::ifstream input_file, generated_output_file, solution_output_file_in;
        std::ofstream solution_output_file;
        usize passed = 0, failed = 0;
        for (const fs::directory_entry& file : fs::directory_iterator(test_case_dir())) {  // 手で作ったテストケース
            const auto input_file_path = file.path();
            if (input_file_path.extension() != ".in") { continue; }
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (usize index = 1; index <= small_gen_num; index++) {
            const auto input_file_path = small_genfile_path(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (usize index = 1; index <= large_gen_num; index++) {
            const auto input_file_path = large_genfile_path(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        return {passed, failed};
    }
};
}  // namespace libtest
