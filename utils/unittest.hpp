#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <future>
#include "logger.hpp"
namespace libtest {
namespace fs = std::filesystem;
template <typename Problem>
class UnitTest
{
public:
    UnitTest(const std::size_t small_gen_num, const std::size_t large_gen_num) : small_gen_num{small_gen_num}, large_gen_num{large_gen_num}, testcase_dir{fs::path(LIBTEST_ROOT) / std::string(Problem::PATH) / "test_cases"}, gen_case_dir{testcase_dir / "generated"} {}
    template <typename Solution>
    bool runTest()
    {
        *g_logger_ptr << Color::GREEN << "[==========] " << Color::RESET << Color::BOLD << "Start (problem=\"" << Problem::NAME << "\",solution=\"" << Solution::NAME << "\")" << Color::RESET << std::endl;
        gen();
        const auto result = test<Solution>();
        summarize(result);
        const bool passed = result.second == 0;
        *g_logger_ptr << Color::GREEN << "[==========] " << Color::RESET << Color::BOLD << (passed ? "Passed" : "Failed") << " (problem=\"" << Problem::NAME << "\",solution=\"" << Solution::NAME << "\")" << Color::RESET << std::endl;
        *g_logger_ptr << std::endl;
        return passed;
    }

private:
    fs::path smallGenFilePath(const std::size_t index, const bool in) const { return gen_case_dir / (std::string("small_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    fs::path largeGenFilePath(const std::size_t index, const bool in) const { return gen_case_dir / (std::string("large_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    template <typename Process>
    std::size_t run(const Process& process)
    {
        std::promise<std::size_t> promise;
        std::future<std::size_t> future = promise.get_future();
        const auto start = std::chrono::high_resolution_clock::now();
        std::thread thread(
            [&](std::promise<std::size_t> promise) {
                process();
                const auto end = std::chrono::high_resolution_clock::now();
                const std::size_t time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                promise.set_value(time_ms);
            },
            std::move(promise));
        if (future.wait_for(std::chrono::milliseconds{Problem::TL * 2}) != std::future_status::timeout) {
            const std::size_t time_ms = future.get();
            return thread.join(), time_ms;
        } else {
            return thread.detach(), Problem::TL * 2;  // 直後にstd::terminate()する
        }
    }
    void gen()
    {
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Generate tests" << Color::RESET << std::endl;
        static std::ofstream input_file;
        static std::ifstream output_file;
        fs::create_directory(testcase_dir), fs::create_directory(gen_case_dir);
        for (std::size_t index = 1; index <= small_gen_num; index++) {
            const fs::path input_file_path = smallGenFilePath(index, true), output_file_path = smallGenFilePath(index, false);
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << Color::GREEN << "[ GENERATE ] " << Color::RESET << input_file_path.filename() << std::endl;
            input_file.open(input_file_path);
            Problem::generateInputSmall(input_file);
            input_file.close(), output_file.open(input_file_path), input_file.open(output_file_path);
            *g_logger_ptr << Color::GREEN << "[ GENERATE ] " << Color::RESET << output_file_path.filename() << std::endl;
            Problem::generateOutputSmall(output_file, input_file);
            input_file.close(), output_file.close();
        }
        for (std::size_t index = 1; index <= large_gen_num; index++) {
            const fs::path input_file_path = largeGenFilePath(index, true);
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << Color::GREEN << "[ GENERATE ] " << Color::RESET << input_file_path.filename() << std::endl;
            input_file.open(input_file_path);
            Problem::generateInputLarge(input_file);
            input_file.close();
        }
    }
    template <typename Solution>
    bool check(const fs::path& input_file_path)
    {
        static std::ifstream input_file, generated_output_file, solution_output_file_in;
        static std::ofstream solution_output_file;
        *g_logger_ptr << Color::GREEN << "[ RUN      ] " << Color::RESET << input_file_path.filename() << std::endl;
        auto solution_out_path = input_file_path;
        solution_out_path.replace_extension(".txt");
        input_file.open(input_file_path), solution_output_file.open(solution_out_path);
        const std::size_t time_ms = run([&]() { Solution::solve(input_file, solution_output_file); });
        bool passed = false;
        if (time_ms == Problem::TL * 2) {
            *g_logger_ptr << Color::RED << "[ TIME OUT ] " << Color::RESET << "Did not end in 2TL (TL=" << Problem::TL << " ms)" << std::endl;
            *g_logger_ptr << Color::RED << "[==========] " << Color::RESET << Color::BOLD << "Abort unittest (problem=\"" << Problem::NAME << "\",solution=\"" << Solution::NAME << "\")" << Color::RESET << std::endl;
            std::terminate();
        } else if (time_ms >= Problem::TL) {
            *g_logger_ptr << Color::RED << "[      TLE ] " << Color::RESET << input_file_path.filename() << " (" << time_ms << " ms,TL=" << Problem::TL << " ms)" << std::endl;
        } else {
            auto generated_out_path = input_file_path;
            generated_out_path.replace_extension(".out");
            if (fs::exists(generated_out_path)) {
                generated_output_file.open(generated_out_path), solution_output_file_in.open(solution_out_path);
                const bool ok = Problem::validateOutput(input_file, generated_output_file, solution_output_file_in);
                if (not ok) {
                    *g_logger_ptr << Color::RED << "[       WA ] " << Color::RESET << input_file_path.filename() << " (" << time_ms << " ms)" << std::endl;
                } else {
                    *g_logger_ptr << Color::GREEN << "[       AC ] " << Color::RESET << input_file_path.filename() << " (" << time_ms << " ms)" << std::endl;
                    passed = true;
                }
                generated_output_file.close(), solution_output_file_in.close();
            } else {
                *g_logger_ptr << Color::GREEN << "[       OK ] " << Color::RESET << input_file_path.filename() << " (" << time_ms << " ms)" << std::endl;
                passed = true;
            }
        }
        fs::remove(solution_out_path);
        input_file.close(), solution_output_file.close();
        return passed;
    }
    template <typename Solution>
    std::pair<std::size_t, std::size_t> test()
    {
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Run tests" << Color::RESET << std::endl;
        std::ifstream input_file, generated_output_file, solution_output_file_in;
        std::ofstream solution_output_file;
        std::size_t passed = 0, failed = 0;
        for (const fs::directory_entry& file : fs::directory_iterator(testcase_dir)) {  // 手で作ったテストケース
            const auto input_file_path = file.path();
            if (input_file_path.extension() != ".in") { continue; }
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (std::size_t index = 1; index <= small_gen_num; index++) {
            const auto input_file_path = smallGenFilePath(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (std::size_t index = 1; index <= large_gen_num; index++) {
            const auto input_file_path = largeGenFilePath(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        return {passed, failed};
    }
    void summarize(const std::pair<std::size_t, std::size_t>& result)
    {
        const std::size_t passed = result.first, failed = result.second;
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Summarize results" << Color::RESET << std::endl;
        if (passed > 0) { *g_logger_ptr << Color::GREEN << "[  PASSED  ] " << Color::RESET << passed << " cases" << std::endl; }
        if (failed > 0) { *g_logger_ptr << Color::RED << "[  FAILED  ] " << Color::RESET << failed << " cases" << std::endl; }
    }
    const std::size_t small_gen_num, large_gen_num;
    const fs::path testcase_dir, gen_case_dir;
};
}  // namespace libtest
