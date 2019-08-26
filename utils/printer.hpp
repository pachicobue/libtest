#pragma once
#include <iostream>
#include <vector>

#include "types.hpp"
namespace libtest {
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (usize i = 0; i < v.size(); i++) { os << (i == 0 ? "" : " ") << v[i]; }
    return os << "\n";
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

private:
    std::ostream& os;
};
}  // namespace libtest
