#pragma once
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>

#include "types.hpp"
namespace libtest {
class scanner
{
public:
    scanner(std::istream& is) : is{is} {}
    explicit operator bool() const { return static_cast<bool>(is); }
    template<typename T>
    auto read()
    {
        T v;
        return is >> v, v;
    }
    template<typename... Types>
    auto read_vals() { return std::tuple<std::decay_t<Types>...>{read<Types>()...}; }
    template<typename T>
    auto read_vec() { return read<T>(); }
    template<typename T, typename... Args>
    auto read_vec(const usize n, Args... args)
    {
        std::vector<decltype(read_vec<T>(args...))> v;
        for (usize i = 0; i < n; i++) { v.push_back(read_vec<T>(args...)); }
        return v;
    }
    template<typename T>
    auto may_read()
    {
        T v;
        return ((is >> v) ? std::make_optional(v) : std::nullopt);
    }
    template<typename... Types>
    auto may_read_vals() { return std::tuple<std::optional<std::decay_t<Types>>...>{may_read<Types>()...}; }
    template<typename T>
    auto may_read_vec() { return may_read<T>(); }
    template<typename T, typename... Args>
    auto may_read_vec(const usize n, Args... args)
    {
        std::vector<decltype(may_read_vec<T>(args...))> v;
        for (usize i = 0; i < n; i++) { v.push_back(may_read_vec<T>(args...)); }
        return v;
    }

private:
    std::istream& is;
};
}  // namespace libtest
