#include "Int.hpp"
#include "string"
#include "vector"
#include "cmath"
#include "algorithm"
#include "iostream"
#include "Karatsuba.hpp"

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
    // for(int i = val.size() - 1; i>=0; i--){
    //     std::cout << val[i];
    // }
    // std::cout << std::endl;
    this->_units = val.size();
    this->_val = val;
    this->_is_positive = positive;
    while(this->_val.back() == 0 && this->_val.size() > 1){
        this->_units--;
        this->_val.pop_back();
    }
    if(this->_val.size() == 1 && this->_val.back() == 0){ // ?????????0, ??????
        this->_is_positive = true;
        this->_length = 1;
    }
    else{
        this->_length = this->_unit_length*(this->_units-1) + static_cast<long long>(log10(this->_val.back()))+1;
    }
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
    // ????????????
    if(this->is_positive() != b.is_positive()){
        return b.is_positive();
    }
    
    // ????????????
    if(this->length() < b.length()){
        return this->is_positive();
    }
    else if(this->length() > b.length()){
        return !this->is_positive();
    }

    // ?????????????????????
    if(this->is_positive()){
        return this->abs_lt(b);
    }
    else{
        return this->abs_gt(b);
    }
}

bool Int::operator>(const Int &b) const{
    // ????????????
    if(this->is_positive() != b.is_positive()){
        return this->is_positive();
    }
    
    // ????????????
    if(this->length() < b.length()){
        return !this->is_positive();
    }
    else if(this->length() > b.length()){
        return this->is_positive();
    }

    // ?????????????????????
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

Int Int::operator+(const Int &b) const{
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

Int Int::operator*(const Int &b) const{
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
    if(this->_units == 1 && this->_val.back() == 0){
        this->_is_positive = true;
        this->_length = 1;
    }
    else{
        this->_length = this->_unit_length*(this->_units-1) + static_cast<long long>(log10(this->_val.back()))+1;
    }
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

Int Int::operator-(const Int &b) const{
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

Int Int::operator/(const Int &b) const{
    if(b.isZero()){
        std::cout << "divided by 0" << std::endl;
        return Int(0);
    }
    if(this->operator<(b)){
        return Int(0);
    }
    return this->knuth_divmod(*this, b, this->_BASE).first;
}

std::pair<long long, Int> Int::get_reciprocal_by_newton(const Int &b, long long target_precision){
    long long len = b.length();
    
    Int dec_part, temp_dec_part, base("1"+std::string(len,'0'));
    
    // ???????????????????????????, ??????????????????
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

    // ?????? x_{k+1} = x_{k}*(2-b*x_{k})
    for(long long i = 1; i <= target_precision*4; i<<=1){
        // ??????x_{k} <= b^{-1}, ??????2-b*x_{k} = 1.xxxx >= 1
        // ????????????????????????2 - b*x_{k}????????????dec_part??????, int_part?????????1
        // 2-b*x_{k}
        base = Int("1"+std::string(len,'0'));
        temp_dec_part = base - (dec_part*b);
        
        // x_{k+1} = x_{k}*(2-b*x_{k})
        // ??????(2-b*x_{k})int_part???1, ??????x_{k}*(2-b*x_{k}) = x_{k} + dec_part*x_{k}
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

Int Int::operator%(const Int& b) const{
    if(this->operator<(b)){
        return *this;
    }
    return this->knuth_divmod(*this, b, this->_BASE).second;
}

Int Int::power(Int b, const Int &mod){
    Int res = 1;
    Int p = *this;
    while(!(b == 0)){
        if(b.is_odd()){
            res = res * p;
            if(res > mod){
                res = res%mod;
            }
        }
        p = p*p;
        if(p > mod){
            p = p % mod;
        }
        b.rightshift();
    }
    return res;
}

long long Int::mod3() const{
    long long ans = 0;
    for(long long i = 0; i < this->_units; i++){
        ans = (ans+this->_val[i])%3;
    }
    return ans;
}

Int Int::Karatsuba_mul(const Int& b){
    return Int(Karatsuba(this->_val, b._val,this->_BASE));
}
// Knuth ?????????
std::pair<Int, Int> Int::knuth_divmod(const Int &a1, const Int &b1, long long base) {
    // ????????????
    // std:: cout << "knuth_div" << std::endl;
    // std::cout << a1.val()  << std::endl << b1.val() << std::endl << "________________" << std::endl;
    long long norm = base / (b1._val.back() + 1);
    Int a = a1.basic_mul(norm); // TODO: basic_mul ?????????long long ???????????????
    Int b = b1.basic_mul(norm);
    Int r;
    std::vector<long long> q_vec(a._val.size());

    for (long long i = a._val.size() - 1; i >= 0; i--) {
        r = r*base;
        r = r + a._val[i];
        long long s1 = b._val.size() < r._val.size() ? r._val[b._val.size()] : 0;
        long long s2 = b._val.size() - 1 < r._val.size() ? r._val[b._val.size() - 1] : 0;
        long long d = (s1 * base + s2) / b._val.back();
        // std::cout << i << "___________________ " << std::endl;
        // std::cout << r.val() << std::endl;
        // std::cout << (s1 * base + s2) << std::endl;
        // std::cout << b.val() << std::endl;
        // std::cout << d << std::endl;
        
        r = r - b * d;
        // std::cout << (b*d).val() << std::endl;
        // std::cout << "___________________ " << std::endl;
        while (r < 0){
            r = r+b;
            d--;
        }
        q_vec[i] = d;
    }
    // for(int i = q_vec.size()-1; i>=0;i--){
    //     std::cout << q_vec[i] << " ";
    // }
    // std::cout << std::endl;
    Int q(q_vec,a1._is_positive == b1._is_positive);
    r._is_positive = a1._is_positive;
    while(!r._val.empty() && r._val.back() == 0){
        r._val.pop_back();
    }
    // TODO: ????????????????????????
    return {q, r.div_ll(norm)};// TODO: ?????????Int ?????? long long ????????? O(N)
}

// b ??????this->_BASE ??????????????????????????????1e18
Int Int::div_ll(long long b){
    std::vector<long long> res(this->_units);
    long long c = 0;
    long long temp;
    for(long long i = this->_units - 1; i >=0; i--){
        temp = c*this->_BASE + this->_val[i];
        // std::cout << i << " " << temp << std::endl;
        res[i] = temp/b;
        c = temp%b;
    }
    return Int(res);
}

// b ??????this->_BASE ??????????????????????????????1e18
Int Int::mod_ll(long long b)const{
    long long c = 0;
    long long temp;
    for(long long i = this->_units - 1; i >=0; i--){
        temp = c*this->_BASE + this->_val[i];
        // std::cout << i << " " << temp << std::endl;
        c = temp%b;
    }
    return Int(c);
}

long long Int::mod5() const{
    return this->_val[0]%5;
}

bool Int::isZero()const{
    return this->_units == 1 && this->_val.back() == 0;
}

Int Int::newton_div(const Int &b){
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