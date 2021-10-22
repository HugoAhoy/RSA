#include "Int.hpp"
#include "string"

Int::Int(std::string val){
    this->_val = val;
}

Int::Int(int val){
    this->_val = std::to_string(val);
}

std::string Int::val(){
    return this->_val;
}