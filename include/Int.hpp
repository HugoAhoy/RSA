// Int.hpp
#ifndef INT_HPP
#define INT_HPP
#include "string"
class Int{
    public:
    Int(std::string val);

    Int(int val);
    
    std::string val();
    // Int operator+(const Int& b);
    // Int operator-(const Int& b);
    // Int operator*(const Int& b);
    // Int operator/(const Int& b);
    // Int mod(const Int& b);

    private:
    std::string _val;
};
#endif

