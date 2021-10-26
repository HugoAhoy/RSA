#include "Int.hpp"
#include "string"
#include "vector"
#include "cmath"

Int::Int(const std::string &val){
    if(!this->is_str_legal(val)){
        ; // raise error
    }
    int bias = 0;
    if(val[0] == '-'){
        this->_is_positive = false;
        bias = 1;
    }
    else{
        this->_is_positive = true;
    }
    long long str_len = val.length();
    long long units = (str_len-bias)/this->_unit_length;
    if((str_len-bias)%this->_unit_length){
        units += 1;
    }
    this->_units = units;
    this->_val = std::vector<long long>(units);
    long long i = 0;
    long long start_pos = str_len - this->_unit_length;
    for(; i < units-1; i++){
        this->_val[i] = std::stoll(val.substr(start_pos,start_pos+this->_unit_length));
        start_pos -= this->_unit_length;
    }
    this->_val[i] = std::stoll(val.substr(bias, start_pos+this->_unit_length));
}

Int::Int(const int &val){
    this->_val = std::vector<long long>(1);
    this->_units = 1;
    if(val < 0){
        this->_is_positive = false;
        this->_val[0] = -val;
    }
    else{
        this->_is_positive = true;
        this->_val[0] = val;
    }
}

Int::Int(const long long &val){
    this->_val = std::vector<long long>(1);
    this->_units = 1;
    if(val < 0){
        this->_is_positive = false;
        this->_val[0] = -val;
    }
    else{
        this->_is_positive = true;
        this->_val[0] = val;
    }
}

bool Int::is_str_legal(const std::string &val){
    if(val.length() == 0){
        return false;
    }
    return true;
}

std::string Int::val(){
    std::string val_str;
    if(!this->_is_positive){
        val_str = "-";
    }
    else{
        val_str="";
    }

    for(int i = this->_units-1; i >= 0 ; i--){
        val_str = val_str+std::to_string(this->_val[i]);
    }
    return val_str;
}