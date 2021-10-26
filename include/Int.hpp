// Int.hpp
#ifndef INT_HPP
#define INT_HPP
#include "string"
#include "vector"
#include "cmath"

class Int{
    public:
    Int(std::string val);

    Int(int val);
    
    Int(long long val);
    
    std::string val();
    // Int operator+(const Int& b);
    // Int operator-(const Int& b);
    // Int operator*(const Int& b);
    // Int operator/(const Int& b);
    // Int mod(const Int& b);

    private:
    bool _is_positive;
    std::vector<long long> _val;
    static const long long _unit_length = 18;
    long long _units;
    static const long long _BASE = static_cast<long long>(1e18);

    bool is_str_legal(const std::string &val);
};
#endif

