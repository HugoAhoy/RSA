#include "Int.hpp"
#include "string"
#include "vector"
#include "cmath"
#include "algorithm"
#include "iostream"

Int::Int(){
    this->_is_positive = true;
    this->_val = std::vector<long long>(1,0);
    this->_units = 1;
    this->_length = 1;
}

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
    while(this->_val.back() == 0 && this->_val.size() > 1){
        this->_units--;
        this->_val.pop_back();
    }
    if(this->_val.size() == 1 && this->_val.back() == 0){
        this->_is_positive = true;
    }
    this->_length = this->_unit_length*(this->_units-1) + static_cast<long long>(log10(this->_val.back()))+1;
}

Int::Int(const Int &b){
    this->_units = b._units;
    this->_val = b._val;
    this->_is_positive = b.is_positive();
    this->_length = b.length();
}


bool Int::is_str_legal(const std::string &val){
    if(val.length() == 0){
        return false;
    }
    return true;
}

std::string Int::val() const{
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

bool Int::abs_gt(const Int &b) const{
    for(int i = this->_units-1; i >= 0; i--){
        if(this->_val[i] != b._val[i]){
            return this->_val[i] > b._val[i];
        }
    }
    return false;
}

bool Int::abs_lt(const Int &b) const{
    for(int i = this->_units-1; i >= 0; i--){
        if(this->_val[i] != b._val[i]){
            return this->_val[i] < b._val[i];
        }
    }
    return false;
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
        return this->abs_lt(b);
    }
    else{
        return this->abs_gt(b);
    }
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
        return this->abs_gt(b);
    }
    else{
        return this->abs_lt(b);
    }
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
    if(this->is_positive() == b.is_positive()){
        if(this->is_positive()){
            return this->basic_add(b);
        }
        else{
            return -(this->basic_add(b));
        }
    }
    else{
        if(this->is_positive()){
            if(this->abs_gt(b)){
                return this->basic_sub(b);
            }
            else{
                return -(b.basic_sub(*this));
            }
        }
        else{
            if(this->abs_gt(b)){
                return -(this->basic_sub(b));
            }
            else{
                return b.basic_sub(*this);
            }
        }
    }
}

Int Int::basic_add(const Int &b) const{
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

Int Int::operator-() const{
    return Int(this->_val, !this->is_positive());
}

Int Int::operator*(const Int &b){
    if(this->is_positive() == b.is_positive()){
        return this->basic_mul(b, true);
    }
    else{
        return this->basic_mul(b, false);
    }
}

Int Int::basic_mul(const Int &b, bool positive) const{
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
    return Int(res, positive);
}

Int Int::_div10(long long n){
    if(n < 0){
        return *this;
    }
    if(n >= this->length()){
        this->_is_positive = true;
        this->_val = std::vector<long long>(1,0);
        this->_units = 1;
        this->_length = 1;
    }
    else{
        long long t = n/this->_unit_length;
        long long base = static_cast<long long>(pow(10, n%this->_unit_length));
        for(int i = n/this->_unit_length; i < this->_units - 1; i++){
            this->_val[i] = this->_val[i]/base;
            this->_val[i] += this->_val[i+1]%base*(this->_BASE/base);
        }
        this->_val[this->_units-1] /= base;
        if(this->_val.back() == 0){
            this->_val.pop_back();
        }
        this->_val = std::vector<long long>(this->_val.begin()+n/this->_unit_length, this->_val.end());
        this->_units = this->_val.size();
        this->_length = this->_length - n;
    }
    return *this;
}

Int Int::rightshift(){
    for(int i = 0; i< this->_units-1; i++){
        this->_val[i] >>=1;
        if(this->_val[i+1] &1){
            this->_val[i] += (this->_BASE>>1);
        }
    }
    this->_val[this->_units-1] >>= 1;
    if(this->_val.back() == 0 && this->_val.size() > 1){
        this->_val.pop_back();
        this->_units--;
    }
    this->_units = this->_val.size();
    this->_length = this->_unit_length*(this->_units-1) + static_cast<long long>(log10(this->_val.back()))+1;
    return *this;
}

Int Int::basic_sub(const Int &b) const{
    std::vector<long long> res(this->_units, 0);
    for(int i = 0; i < b._units; i++){
        res[i] = this->_val[i] - b._val[i];
    }
    for(int i = 0; i < b._units; i++){
        if(res[i] < 0){
            res[i+1]--;
            res[i] += this->_BASE;
        }
    }
    for(int i = b._units; i < this->_units; i++){
        res[i] += this->_val[i];
    }
    return Int(res);
}

Int Int::operator-(const Int &b){
    if(this->is_positive() == b.is_positive()){
        if(this->is_positive() == true){
            if(this->operator>(b)){
                return this->basic_sub(b);
            }
            else {
                return -(b.basic_sub(*this));
            }
        }
        else{
            if(this->operator>(b)){
                return b.basic_sub(*this);
            }
            else {
                return -(this->basic_sub(b));
            }
        }
    }
    else{
        if(this->is_positive()){
            return this->basic_add(b);
        }
        else{
            return -(this->basic_add(b));
        }
    }
}

Int Int::operator/(const Int &b){
    if(this->operator<(b)){
        return *this;
    }
    auto ret = this->get_reciprocal_by_newton(b, this->length());
    Int res = this->operator*(ret.second);
    res._div10(ret.first);
    Int remainder = this->operator-(res*b);
    if(remainder > b){
        res = res + div_by_binary_search(remainder, b);
    }
    return res;
}

std::pair<long long, Int> Int::get_reciprocal_by_newton(const Int &b, long long target_precision){
    long long len = b.length();
    
    Int dec_part, temp_dec_part, base("1"+std::string(len,'0'));
    
    // 找到一个最优起始点, 可以改成二分
    int i = 2;
    for(; i < 10; i++){
        if(Int(i)*b > base){
            dec_part = Int(i-1);
            break;
        }
    }
    if(i == 10){
        dec_part = Int(9);
    }

    // 迭代 x_{k+1} = x_{k}*(2-b*x_{k})
    for(long long i = 1; i <= target_precision*4; i<<=1){
        // 由于x_{k} <= b^{-1}, 所以2-b*x_{k} = 1.xxxx >= 1
        // 这意味着我们计算2 - b*x_{k}只需要算dec_part就行, int_part永远为1
        // 2-b*x_{k}
        base = Int("1"+std::string(len,'0'));
        temp_dec_part = base - (dec_part*b);
        
        // x_{k+1} = x_{k}*(2-b*x_{k})
        // 因为(2-b*x_{k})int_part为1, 所以x_{k}*(2-b*x_{k}) = x_{k} + dec_part*x_{k}
        dec_part = dec_part*(base + temp_dec_part);
        // long long len_to_truncate = dec_part.length()-i*2;
        // dec_part._div10(len_to_truncate);
        // len = 2*len-len_to_truncate;
        len = 2*len;
    }

    return std::make_pair(len, dec_part);
}

Int Int::div_by_binary_search(const Int &a, const Int &b){
    if(a < b){
        return a;
    }
    long long len_diff = a.length() - b.length();
    Int lower("1"+ std::string(len_diff, '0'));
    if(lower*b > a){
        lower._div10(1);
    }
    Int upper = Int(10)*lower;
    Int mid;
    while(lower < upper){
        mid = (lower+upper+Int(1)).rightshift();
        Int temp_res = mid*b;
        if(temp_res > a){
            upper = mid-Int(1);
        }
        else{
            lower = mid;
        }
    }
    return lower;
}