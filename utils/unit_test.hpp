#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <sstream>

#include "logger.hpp"
namespace libtest {
namespace fs = std::filesystem;
template<typename Problem>
class unit_test
{
    using color = typename ansi_sgr::color;
    using attr  = typename ansi_sgr::attribute;

public:
    using problem_type = Problem;
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
    unit_test(const std::size_t small_gen_num, const std::size_t large_gen_num) : small_gen_num{small_gen_num}, large_gen_num{large_gen_num}, testcase_dir{fs::path(LIBTEST_ROOT) / std::string(problem_type::path) / "test_cases"}, gen_case_dir{testcase_dir / "generated"} {}
    template<typename Solution>
    bool run_test(bool silent = false)
    {
        *g_logger_ptr << base_color << "[==========] " << reset << bold_message_color << "Start (problem=\"" << problem_type::name << "\",solution=\"" << Solution::name << "\")" << reset << std::endl;
        if (silent) { mute_log(); }
        gen();
        const auto result        = test<Solution>();
        const std::size_t passed = result.first, failed = result.second;
        *g_logger_ptr << base_color << "[----------] " << reset << bold_message_color << "Summarize results" << reset << std::endl;
        if (silent) { unmute_log(); }
        if (passed > 0) { *g_logger_ptr << passed_color << "[  PASSED  ] " << reset << message_color << passed << " cases" << reset << std::endl; }
        if (failed > 0) { *g_logger_ptr << failed_color << "[  FAILED  ] " << reset << message_color << failed << " cases" << reset << std::endl; }
        *g_logger_ptr << base_color << "[==========] " << reset << bold_message_color << "End (problem=\"" << problem_type::name << "\",solution=\"" << Solution::name << "\")" << reset << std::endl;
        *g_logger_ptr << std::endl;
        return passed;
    }

private:
    fs::path small_genfile_path(const std::size_t index, const bool in) const { return gen_case_dir / (std::string("small_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    fs::path large_genfile_path(const std::size_t index, const bool in) const { return gen_case_dir / (std::string("large_") + std::to_string(index) + (in ? std::string(".in") : std::string(".out"))); }
    template<typename Process>
    std::size_t run(const Process& process)
    {
        std::promise<std::size_t> promise;
        std::future<std::size_t> future = promise.get_future();
        const auto start                = std::chrono::high_resolution_clock::now();
        std::thread thread(
            [&](std::promise<std::size_t> promise) {
                process();
                const auto end            = std::chrono::high_resolution_clock::now();
                const std::size_t time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                promise.set_value(time_ms);
            },
            std::move(promise));
        if (future.wait_for(std::chrono::milliseconds{problem_type::time_limit * 2}) != std::future_status::timeout) {
            const std::size_t time_ms = future.get();
            return thread.join(), time_ms;
        } else {
            return thread.detach(), problem_type::time_limit * 2;  // 直後にstd::terminate()する
        }
    }
    void gen()
    {
        *g_logger_ptr << base_color << "[----------] " << reset << bold_message_color << "Generate tests" << reset << std::endl;
        static std::ofstream input_file;
        static std::ifstream output_file;
        fs::create_directory(testcase_dir), fs::create_directory(gen_case_dir);
        for (std::size_t index = 1; index <= small_gen_num; index++) {
            const fs::path input_file_path = small_genfile_path(index, true), output_file_path = small_genfile_path(index, false);
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << ac_color << "[ GENERATE ] " << reset << message_color << input_file_path.filename() << reset << std::endl;
            input_file.open(input_file_path);
            problem_type::generate_input_small(input_file);
            input_file.close(), output_file.open(input_file_path), input_file.open(output_file_path);
            *g_logger_ptr << ac_color << "[ GENERATE ] " << reset << message_color << output_file_path.filename() << reset << std::endl;
            problem_type::generate_output_small(output_file, input_file);
            input_file.close(), output_file.close();
        }
        for (std::size_t index = 1; index <= large_gen_num; index++) {
            const fs::path input_file_path = large_genfile_path(index, true);
            if (fs::exists(input_file_path)) { continue; }
            *g_logger_ptr << ac_color << "[ GENERATE ] " << reset << message_color << input_file_path.filename() << reset << std::endl;
            input_file.open(input_file_path);
            problem_type::generate_input_large(input_file);
            input_file.close();
        }
    }
    template<typename Solution>
    bool check(const fs::path& input_file_path)
    {
        static std::ifstream input_file, generated_output_file, solution_output_file_in;
        static std::ofstream solution_output_file;
        *g_logger_ptr << ac_color << "[ RUN      ] " << reset << message_color << input_file_path.filename() << reset << std::endl;
        auto solution_out_path = input_file_path;
        solution_out_path.replace_extension(".txt");
        input_file.open(input_file_path), solution_output_file.open(solution_out_path);
        const std::size_t time_ms = run([&]() { Solution::solve(input_file, solution_output_file); });
        bool passed               = false;
        if (time_ms == problem_type::time_limit * 2) {
            unmute_log();
            *g_logger_ptr << bold_fatal_color << "[ TIME OUT ] " << reset << fatal_color << "Did not end in time_limit*2 (time_limit=" << problem_type::time_limit << " ms)" << reset << std::endl;
            *g_logger_ptr << fatal_color << "[==========] " << reset << bold_fatal_color << "Abort (problem=\"" << problem_type::name << "\",solution=\"" << Solution::name << "\")" << reset << std::endl;
            std::terminate();
        } else if (time_ms >= problem_type::time_limit) {
            *g_logger_ptr << tle_color << "[      TLE ] " << reset << message_color << input_file_path.filename() << " (" << time_ms << " ms,time_limit=" << problem_type::time_limit << " ms)" << reset << std::endl;
        } else {
            auto generated_out_path = input_file_path;
            generated_out_path.replace_extension(".out");
            if (fs::exists(generated_out_path)) {
                generated_output_file.open(generated_out_path), solution_output_file_in.open(solution_out_path);
                const bool ok = problem_type::validate_output(input_file, generated_output_file, solution_output_file_in);
                if (not ok) {
                    *g_logger_ptr << wa_color << "[       WA ] " << reset << message_color << input_file_path.filename() << " (" << time_ms << " ms)" << reset << std::endl;
                } else {
                    *g_logger_ptr << ac_color << "[       AC ] " << reset << message_color << input_file_path.filename() << " (" << time_ms << " ms)" << reset << std::endl;
                    passed = true;
                }
                generated_output_file.close(), solution_output_file_in.close();
            } else {
                *g_logger_ptr << ac_color << "[       AC ] " << reset << message_color << input_file_path.filename() << " (" << time_ms << " ms)" << reset << std::endl;
                passed = true;
            }
        }
        fs::remove(solution_out_path);
        input_file.close(), solution_output_file.close();
        return passed;
    }
    template<typename Solution>
    std::pair<std::size_t, std::size_t> test()
    {
        *g_logger_ptr << base_color << "[----------] " << reset << bold_message_color << "Run tests" << reset << std::endl;
        std::ifstream input_file, generated_output_file, solution_output_file_in;
        std::ofstream solution_output_file;
        std::size_t passed = 0, failed = 0;
        for (const fs::directory_entry& file : fs::directory_iterator(testcase_dir)) {  // 手で作ったテストケース
            const auto input_file_path = file.path();
            if (input_file_path.extension() != ".in") { continue; }
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (std::size_t index = 1; index <= small_gen_num; index++) {
            const auto input_file_path = small_genfile_path(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        for (std::size_t index = 1; index <= large_gen_num; index++) {
            const auto input_file_path = large_genfile_path(index, true);
            (check<Solution>(input_file_path) ? passed : failed)++;
        }
        return {passed, failed};
    }
    const std::size_t small_gen_num, large_gen_num;
    const fs::path testcase_dir, gen_case_dir;
};
}  // namespace libtest
