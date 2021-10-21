// Int.hpp
#ifndef INT_HPP
#define INT_HPP
#include "string"
class Int{
    public:
    Int():_val("0"){}
    
    std::string val(){
        return this->_val;
    }

    Int operator+(const Int& b){
        return *this;
    }
    Int operator-(const Int& b){
        return *this;
    }
    Int operator*(const Int& b){
        return *this;
    }
    Int operator/(const Int& b){
        return *this;
    }
    Int mod(const Int& b){
        return *this;
    }

    private:
    std::string _val;
};
#endif

