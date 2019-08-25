#include <iostream>
namespace libtest {
class ansi_sgr
{
public:
    enum class color {
        black = 30,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white,
    };
    enum class attribute {
        reset = 0,
        bold  = 1,
        thin,
        italic,
        under_line,
        blink,
        blink_hi,
        invert,
        hide,
        strike_out,
    };
    constexpr ansi_sgr(const color col = color::white, const attribute attr = attribute::reset) : m_color{col}, m_attr{attr} {}
    std::string to_string() const { return "\e[" + std::to_string(static_cast<int>(m_attr)) + ";" + std::to_string(static_cast<int>(m_color)) + "m"; }

private:
    color m_color;
    attribute m_attr;
};

}  // namespace libtest
