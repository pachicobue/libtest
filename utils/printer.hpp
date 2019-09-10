#pragma once
#include <cassert>
#include <iostream>
#include <vector>

#include "ansi_sgr.hpp"
#include "types.hpp"
namespace libtest {
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (usize i = 0; i < v.size(); i++) { os << (i == 0 ? "" : " ") << v[i]; }
    return os;
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) { return os << p.first << " " << p.second; }
template<typename TupType, size_t... I>
std::ostream& print(std::ostream& os, const TupType& _tup, std::index_sequence<I...>) { return os << "(", (..., (os << (I == 0 ? "" : ", ") << std::get<I>(_tup))), os << ")\n"; }
template<typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& _tup) { return print(os, _tup, std::make_index_sequence<sizeof...(T)>()); }
class printer
{
public:
    printer(std::ostream& os) : os{os} {}
    void println() {}
    template<typename T>
    void println(const T& t) { os << t << "\n"; }
    template<typename T, typename... Args>
    void println(const T& t, Args... args) { os << t << " ", println(args...); }
    template<typename... Args>
    void printf(const std::string& s, const Args... args) { format_rec(s, 0, args...); }
    template<typename... Args>
    void cprintln(const ansi_sgr& command, Args... args) { os << command.to_string(), println(args...), os << ansi_sgr{}.to_string(); }
    template<typename... Args>
    void cprintf(const ansi_sgr& command, Args... args) { os << command.to_string(), printf(args...), os << ansi_sgr{}.to_string(); }

private:
    void format_rec(const std::string& s, usize index)
    {
        for (; index < s.size();) {
            if (s[index] == '%') {
                assert(index + 1 < s.size() and s[index + 1] == '%');
                index += 2, os << '%';
            } else {
                os << s[index++];
            }
        }
    }
    template<typename T, typename... Args>
    void format_rec(const std::string& s, usize index, const T& t, const Args... args)
    {
        for (; index < s.size();) {
            if (s[index] == '%') {
                if (index + 1 < s.size() and s[index + 1] == '%') {
                    index += 2, os << '%';
                } else {
                    return os << t, format_rec(s, ++index, args...), static_cast<void>(0);
                }
            } else {
                os << s[index++];
            }
        }
        assert(false);
    }
    std::ostream& os;
};
auto g_printer = printer{std::cout};
template<typename... Args>
void printf(const Args... args) { g_printer.printf(args...); }
template<typename... Args>
void println(const Args... args) { g_printer.println(args...); }
template<typename... Args>
void cprintf(const Args... args) { g_printer.cprintf(args...); }
template<typename... Args>
void cprintln(const Args... args) { g_printer.cprintln(args...); }
}  // namespace libtest
