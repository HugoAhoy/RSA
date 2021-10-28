#include "Int.hpp"
#include "string"
#include "vector"
#include "cmath"
#include "algorithm"
#include "iostream"

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
        this->_val[i] = std::stoll(val.substr(start_pos,this->_unit_length));
        start_pos -= this->_unit_length;
    }
    this->_val[i] = std::stoll(val.substr(bias, start_pos+this->_unit_length-bias));
}

Int::Int(const int &val){
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
    this->_units = this->length()/this->_unit_length;
    if(this->length()%this->_unit_length){
        this->_units += 1;
    }
    this->_val = std::vector<long long>(this->_units);
    for(int i = 0; i < this->_units; i++){
        this->_val[i] = val_positive%this->_BASE;
        val_positive = val_positive/this->_BASE;
    }
}

Int::Int(const long long &val){
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
    this->_units = this->length()/this->_unit_length;
    if(this->length()%this->_unit_length){
        this->_units += 1;
    }
    this->_val = std::vector<long long>(this->_units);
    for(int i = 0; i < this->_units; i++){
        this->_val[i] = val_positive%this->_BASE;
        val_positive = val_positive/this->_BASE;
    }
}

Int::Int(const std::vector<long long> &val, bool positive){
    this->_units = val.size();
    this->_val = val;
    this->_is_positive = positive;
    while(this->_val.back() == 0){
        this->_units--;
        this->_val.pop_back();
    }
    this->_length = this->_unit_length*(this->_units-1) + static_cast<long long>(log10(this->_val.back()))+1;
}


bool Int::is_str_legal(const std::string &val){
    if(val.length() == 0){
        return false;
    }
    return true;
}

std::string Int::val(){
    std::string sub;
    long long val_length = this->length() + !this->is_positive();
    std::string val_str(val_length,'0');
    if(!this->is_positive()){
        val_str[0] = '-';
    }

    int idx;
    for(int i = 0; i < this->_units; i++){
        sub = std::to_string(this->_val[i]);
        idx = val_length - i*this->_unit_length - 1;
        for(int j = sub.length()-1; j >= 0; j--, idx--){
            val_str[idx] = sub[j];
        }
    }
    return val_str;
}

long long Int::length() const{
    return this->_length;
}

bool Int::is_positive() const{
    return this->_is_positive;
}

bool Int::is_odd() const{
    return this->_val[0]&1;
}

bool Int::operator<(const Int &b) const{
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

bool Int::operator>(const Int &b) const{
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

bool Int::operator<=(const Int &b) const{
    return !this->operator>(b);
}

bool Int::operator>=(const Int &b) const{
    return !this->operator<(b);
}

bool Int::operator==(const Int &b) const{
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

Int Int::operator+(const Int &b){
    if(this->is_positive() && b.is_positive()){
        return this->basic_add(b);
    }
    else{
        throw -1;
    }
}

Int Int::basic_add(const Int &b){
    long long res_units = std::max(this->_units, b._units) + 1;
    std::vector<long long> res(res_units);
    long long c = 0;
    long long end_idx = std::min(this->_units, b._units);
    int i = 0;
    for(; i < end_idx; i++){
        res[i] = this->_val[i] + b._val[i] + c;
        c = res[i] / this->_BASE;
        res[i] = res[i] % this->_BASE;
    }
    while(this->_units > i){
        res[i] = this->_val[i] + c;
        c = res[i] / this->_BASE;
        res[i] = res[i] % this->_BASE;
        i++;
    }
    while(b._units > i){
        res[i] = b._val[i] + c;
        c = res[i] / this->_BASE;
        res[i] = res[i] % this->_BASE;
        i++;
    }
    while(c !=0 && res_units > i){
        res[i] = c;
        c = res[i] / this->_BASE;
        res[i] = res[i] % this->_BASE;
        i++;
    }
    return Int(res);
}

Int Int::operator-(){
    this->_is_positive = !this->_is_positive;
    return *this;
}

Int Int::operator*(const Int &b){
    Int res = this->basic_mul(b);
    if(this->is_positive() == b.is_positive()){
        return res;
    }
    else{
        return -res;
    }
}

Int Int::basic_mul(const Int &b){
    long long res_units = this->_units+b._units+1;
    std::vector<long long> res(res_units, 0);
    for(int i = 0; i < this->_units; i++){
        long long c = 0;
        for(int j = 0; j < b._units; j++){
            res[i+j] += this->_val[i] * b._val[j]+c;
            c = res[i+j]/this->_BASE;
            res[i+j] = res[i+j]%this->_BASE;
        }
        res[i+b._units] += c;
    }
    if(res[this->_units+b._units] >= this->_BASE){
        res[this->_units+b._units+1] += res[this->_units+b._units] /this->_BASE;
        res[this->_units+b._units] = res[this->_units+b._units] % this->_BASE;
    }
    return Int(res);
}