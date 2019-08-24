#pragma once
#include <iostream>
#include <memory>

#include "ansi.hpp"
namespace libtest {
class logger
{
public:
    logger(std::ostream& os) : os{os} {}
    template<typename T>
    friend logger& operator<<(logger& logger, const T& val) { return logger.silent ? logger : (logger.os << val, logger); }
    friend logger& operator<<(logger& logger, std::ostream& (*f)(std::ostream&)) { return logger.silent ? logger : (logger.os << f, logger); }
    friend logger& operator<<(logger& logger, const ansi_sgr command)
    {
        if (logger.silent) { return logger; }
        return (logger.os << command.to_string(), logger);
    }
    void mute() { silent = true; }
    void unmute() { silent = false; }

private:
    bool silent = false;
    std::ostream& os;
};  // namespace libtest
std::unique_ptr<logger> g_logger_ptr = std::make_unique<logger>(std::cout);
void mute_log() { g_logger_ptr->mute(); }
void unmute_log() { g_logger_ptr->unmute(); }
void redirect_log(std::ostream& os) { g_logger_ptr = std::make_unique<logger>(os); }
}  // namespace libtest
