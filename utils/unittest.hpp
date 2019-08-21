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
    UnitTest(const std::size_t small_gen_num, const std::size_t large_gen_num) : small_gen_num{small_gen_num}, large_gen_num{large_gen_num}, testcase_path{fs::path(LIBTEST_ROOT) / std::string(Problem::NAME) / "cases"}
    {
        *g_logger_ptr << Color::GREEN << "[==========] " << Color::RESET << Color::BOLD << Problem::NAME << Color::RESET << std::endl;
        gen();
    }
    template <typename Solver>
    bool runTest()
    {
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Running tests" << Color::RESET << std::endl;
        std::ifstream input_file, generated_output_file, solver_output_file_in;
        std::ofstream solver_output_file;
        std::size_t passed = 0, failed = 0;
        for (const fs::directory_entry& file : fs::directory_iterator(testcase_path)) {
            const auto path = file.path();
            if (path.extension() != ".in") { continue; }
            *g_logger_ptr << Color::GREEN << "[ RUN      ] " << Color::RESET << path.filename() << std::endl;
            auto solver_out_path = path;
            solver_out_path.replace_extension(".txt");
            input_file.open(path), solver_output_file.open(solver_out_path);
            const std::size_t time_ms = run([&]() { Solver::solve(input_file, solver_output_file); });
            if (time_ms == Problem::TL * 2) {
                *g_logger_ptr << Color::RED << "[ TIME OUT ] " << Color::RESET << "Did not end in 2TL(TL=" << Problem::TL << " ms)" << std::endl;
                std::terminate();
            } else if (time_ms >= Problem::TL) {
                failed++, *g_logger_ptr << Color::RED << "[ TIME OUT ] " << Color::RESET << path.filename() << " (" << time_ms << "ms)" << std::endl;
            } else {
                auto generated_out_path = path;
                generated_out_path.replace_extension(".out");
                if (fs::exists(generated_out_path)) {
                    generated_output_file.open(generated_out_path), solver_output_file_in.open(solver_out_path);
                    const bool ok = Problem::validateOutputSmall(input_file, generated_output_file, solver_output_file_in);
                    if (not ok) {
                        failed++, *g_logger_ptr << Color::RED << "[  FAILED  ] " << Color::RESET << path.filename() << " (" << time_ms << " ms)" << std::endl;
                    } else {
                        passed++, *g_logger_ptr << Color::GREEN << "[       OK ] " << Color::RESET << path.filename() << " (" << time_ms << " ms)" << std::endl;
                    }
                    generated_output_file.close(), solver_output_file_in.close();
                } else {
                    passed++, *g_logger_ptr << Color::GREEN << "[       OK ] " << Color::RESET << path.filename() << " (" << time_ms << " ms)" << std::endl;
                }
            }
            input_file.close(), solver_output_file.close();
        }
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Summarizing results" << Color::RESET << std::endl;
        if (passed > 0) { *g_logger_ptr << Color::GREEN << "[  PASSED  ] " << Color::RESET << passed << " cases" << std::endl; }
        if (failed > 0) { *g_logger_ptr << Color::RED << "[  FAILED  ] " << Color::RESET << failed << " cases" << std::endl; }
        *g_logger_ptr << Color::GREEN << "[==========] " << Color::RESET << std::endl;
        *g_logger_ptr << std::endl;
        return failed == 0;
    }

private:
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
            return thread.detach(), Problem::TL * 2;
        }
    }
    void gen()
    {
        *g_logger_ptr << Color::GREEN << "[----------] " << Color::RESET << Color::BOLD << "Generating tests" << Color::RESET << std::endl;
        std::ofstream ofs;
        std::ifstream ifs;
        fs::create_directory(testcase_path);
        for (std::size_t index = 0; index < small_gen_num; index++) {
            const fs::path input_file_path = testcase_path / (std::string("generated_small_") + std::to_string(index) + std::string(".in"));
            const fs::path output_file_path = testcase_path / (std::string("generated_small_") + std::to_string(index) + std::string(".out"));
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << Color::GREEN << "[ GENERATE ] " << Color::RESET << input_file_path.filename() << std::endl;
            ofs.open(input_file_path);
            Problem::generateInputSmall(ofs);
            ofs.close(), ifs.open(input_file_path), ofs.open(output_file_path);
            Problem::generateOutputSmall(ifs, ofs);
            ofs.close(), ifs.close();
        }
        for (std::size_t index = 0; index < large_gen_num; index++) {
            const fs::path input_file_path = testcase_path / (std::string("generated_large_") + std::to_string(index) + std::string(".in"));
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << Color::GREEN << "[ GENERATE ] " << Color::RESET << input_file_path.filename() << std::endl;
            ofs.open(input_file_path);
            Problem::generateInputLarge(ofs);
            ofs.close();
        }
    }
    const std::size_t small_gen_num, large_gen_num;
    const fs::path testcase_path;
};
}  // namespace libtest
