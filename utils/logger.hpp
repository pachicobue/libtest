#pragma once
#include <iostream>
#include <memory>
namespace libtest {
enum class Color
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BOLD,
    RESET,
};
class Logger
{
public:
    Logger(std::ostream& os) : os{os} {}
    template <typename T>
    friend Logger& operator<<(Logger& logger, const T& val) { return logger.silent ? logger : (logger.os << val, logger); }
    friend Logger& operator<<(Logger& logger, std::ostream& (*f)(std::ostream&)) { return logger.silent ? logger : (logger.os << f, logger); }
    friend Logger& operator<<(Logger& logger, const Color& color)
    {
        if (logger.silent) { return logger; }
        switch (color) {
        case Color::BLACK:
            return (logger.os << "\033[30m", logger);
        case Color::RED:
            return (logger.os << "\033[31m", logger);
        case Color::GREEN:
            return (logger.os << "\033[32m", logger);
        case Color::YELLOW:
            return (logger.os << "\033[33m", logger);
        case Color::BLUE:
            return (logger.os << "\033[34m", logger);
        case Color::MAGENTA:
            return (logger.os << "\033[35m", logger);
        case Color::CYAN:
            return (logger.os << "\033[36m", logger);
        case Color::WHITE:
            return (logger.os << "\033[37m", logger);
        case Color::BOLD:
            return (logger.os << "\033[1m", logger);
        case Color::RESET:
            return (logger.os << "\033[0m", logger);
        default:
            return logger;
        }
    }
    void mute() { silent = true; }
    void unmute() { silent = false; }

private:
    bool silent = false;
    std::ostream& os;
};
std::unique_ptr<Logger> g_logger_ptr = std::make_unique<Logger>(std::cout);
void setRedirect(std::ostream& os) { g_logger_ptr = std::make_unique<Logger>(os); }
}  // namespace libtest
