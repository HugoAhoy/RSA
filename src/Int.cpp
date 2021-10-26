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
    this->_length = str_len-bias;
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
        this->_length = static_cast<long long>(log10(-val))+1;
    }
    else{
        this->_is_positive = true;
        this->_val[0] = val;
        if (val == 0){
            this->_length = 1;
        }
        else{
            this->_length = static_cast<long long>(log10(val))+1;
        }
    }
}

Int::Int(const long long &val){
    if (val >= this->_BASE){
        this->_units =2;
    }
    else{
        this->_units = 1;
    }
    this->_val = std::vector<long long>(this->_units);
    long long val_positive;
    if(val < 0){
        this->_is_positive = false;
        val_positive = -val;
    }
    else{
        this->_is_positive = true;
        val_positive = val;
    }
    if(val == 0){
        this->_length = 1;
    }
    else{
        this->_length = static_cast<long long>(log10(val_positive))+1;
    }
    for(int i = 0; i < this->_units; i++){
        this->_val[i] = val_positive%this->_BASE;
        val_positive = val_positive/this->_BASE;
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

long long Int::length() const{
    return this->_length;
}

bool Int::is_positive() const{
    return this->_is_positive;
}

bool Int::operator<(const Int &b){
    // 正负不同
    if(this->is_positive() != b.is_positive()){
        return b.is_positive();
    }
    
    // 长度不同
    if(this->length() < b.length()){
        return this->is_positive();
    }
    else if(this->length() > b.length()){
        return !this->is_positive();
    }

    // 正负长度都相同
    if(this->is_positive()){
        for(int i = this->_units-1; i >= 0; i--){
            if(this->_val[i] != b._val[i]){
                return this->_val[i] < b._val[i];
            }
        }
    }
    else{
        for(int i = this->_units-1; i >= 0; i--){
            if(this->_val[i] != b._val[i]){
                return this->_val[i] > b._val[i];
            }
        }
    }
    return false;
}

bool Int::operator>(const Int &b){
    // 正负不同
    if(this->is_positive() != b.is_positive()){
        return this->is_positive();
    }
    
    // 长度不同
    if(this->length() < b.length()){
        return !this->is_positive();
    }
    else if(this->length() > b.length()){
        return this->is_positive();
    }

    // 正负长度都相同
    if(this->is_positive()){
        for(int i = this->_units-1; i >= 0; i--){
            if(this->_val[i] != b._val[i]){
                return this->_val[i] > b._val[i];
            }
        }
    }
    else{
        for(int i = this->_units-1; i >= 0; i--){
            if(this->_val[i] != b._val[i]){
                return this->_val[i] < b._val[i];
            }
        }
    }
    return false;
}

bool Int::operator<=(const Int &b){
    return !this->operator>(b);
}

bool Int::operator>=(const Int &b){
    return !this->operator<(b);
}

bool Int::operator==(const Int &b){
    if(this->is_positive() != b.is_positive()){
        return false;
    }
    
    if(this->length() != b.length()){
        return false;
    }

    for(int i = this->_units-1; i >= 0; i--){
        if(this->_val[i] != b._val[i]){
            return false;
        }
    }
    return true;
}
