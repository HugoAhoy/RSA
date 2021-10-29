// Int.hpp
#ifndef INT_HPP
#define INT_HPP
#include "string"
#include "vector"
#include "cmath"

class Int{
    public:
    Int(const std::string &val);

    Int(const int &val);
    
    Int(const long long &val);

    Int(const std::vector<long long> &val, bool positive=true);

    Int(const Int &b);
    
    std::string val();

    long long length() const;
    bool is_positive() const;
    bool is_odd() const;

    bool operator >(const Int &b) const;
    bool operator <(const Int &b) const;
    bool operator <=(const Int &b) const;
    bool operator >=(const Int &b) const;
    bool operator ==(const Int &b) const;
    Int operator+(const Int &b);
    Int operator-(const Int& b);
    Int operator-() const;
    Int operator*(const Int& b);
    // Int operator/(const Int& b);
    // Int operator%(const Int& b);

    private:
    bool _is_positive;
    std::vector<long long> _val;
    static const long long _unit_length = 9;
    long long _units;
    long long _length;
    static const long long _BASE = static_cast<long long>(1e9);

    bool is_str_legal(const std::string &val);
    Int basic_add(const Int &b) const;
    Int basic_mul(const Int &b, bool positive = true) const;
    Int basic_sub(const Int &b) const;
    bool abs_gt(const Int &b) const;
    bool abs_lt(const Int &b) const;
    int _div10();
};
#endif

