#include "Karatsuba.hpp"
#include "algorithm"
#include "string"
#include "iostream"
#include "iomanip"
#include "vector"
static std::vector<long long> frontpad(std::vector<long long> vec, long long n);
static std::vector<long long> add(std::vector<long long> a, std::vector<long long> b, long long base);
static std::vector<long long> sub(std::vector<long long> a, std::vector<long long> b, long long base);
static std::vector<long long> basic_mul(std::vector<long long> a, std::vector<long long> b, long long base);
void print(std::vector<long long> res, long long width);

std::vector<long long> Karatsuba(std::vector<long long> a, std::vector<long long> b, long long base){
    long long a_size = a.size(), b_size = b.size();
    if(a_size == 1 || b_size == 1||a_size >= b_size*b_size || a_size*a_size <= b_size){
        return basic_mul(a,b,base);
    }
    std::vector<long long> A;
    std::vector<long long> B;
    std::vector<long long> C;
    std::vector<long long> D;
    long long mid, mid_l;
    if(a_size >= b_size){
        mid = a_size>> 1;
        mid_l = a_size -mid;
        A.assign(a.begin()+mid_l, a.end());
        B.assign(a.begin(), a.begin()+mid_l);
        if(mid_l >= b_size){
            return add(frontpad(Karatsuba(A,b,base),mid_l),Karatsuba(B,b, base),base);
        }
        else{
            C.assign(b.begin()+mid_l, b.end());
            D.assign(b.begin(), b.begin()+mid_l);
        }
    }
    else {
        mid = b_size>> 1;
        mid_l = b_size -mid;
        A.assign(b.begin()+mid_l, b.end());
        B.assign(b.begin(), b.begin()+mid_l);
        if(mid_l >= a_size){
            return add(frontpad(Karatsuba(A,a,base),mid_l),Karatsuba(B,a, base),base);
        }
        else{
            C.assign(a.begin()+mid_l, a.end());
            D.assign(a.begin(), a.begin()+mid_l);
        }
    }
    std::vector<long long> AC, BD, MID;
    AC = Karatsuba(A,C, base);
    BD = Karatsuba(B,D, base);
    MID = sub(Karatsuba(add(A,B,base),add(C,D,base),base),add(AC,BD,base), base);
    return add(frontpad(AC,mid_l<<1),add(frontpad(MID, mid_l),BD,base),base);
}

static std::vector<long long> frontpad(std::vector<long long> vec, long long n){
    long long head = vec.size()-1;
    vec.resize(vec.size() + n, 0);
    do{
        vec[head+n] = vec[head];
    }while(head--);

    for(long long i = 0; i < n; i++){
        vec[i] = 0;
    }
    return vec;
}

static std::vector<long long> add(std::vector<long long> a, std::vector<long long> b, long long base){
    long long a_size = a.size(), b_size = b.size();
    std::vector<long long> res(std::max(a.size(), b.size())+1);
    long long c= 0;
    for(long long i = 0; i < res.size(); i++){
        res[i] = ((i < a_size)?a[i]:0)+((i < b_size)?b[i]:0)+c;
        c = res[i] / base;
        res[i] %=base;
    }
    while(!res.empty()&&res.back() ==0){
        res.pop_back();
    }
    return res;
}

static std::vector<long long> sub(std::vector<long long> a, std::vector<long long> b, long long base){
    // a > b
    long long a_size = a.size(), b_size = b.size();
    std::vector<long long> res(a_size, 0);
    for(int i = 0; i < b_size; i++){
        res[i] = a[i] - b[i];
    }
    for(int i = 0; i < b_size; i++){
        if(res[i] < 0){
            res[i+1]--;
            res[i] += base;
        }
    }
    for(int i = b_size; i < a_size; i++){
        res[i] += a[i];
    }
    while(!res.empty() && res.back() == 0){
        res.pop_back();
    }
    return res;
}

static std::vector<long long> basic_mul(std::vector<long long> a, std::vector<long long> b, long long base){
    long long a_size = a.size(), b_size = b.size();
    std::vector<long long> res(a_size + b_size,0);
    if(a_size > b_size){
        for(int i = 0 ; i < b_size; i++){
            long long c = 0;
            for(int j = 0; j < a_size; j++){
                res[i+j] += b[i]*a[j]+c;
                c = res[i+j]/base;
                res[i+j] %= base;
            }
            if(c){
                res[i+a_size]+=c;
            }
        }
    }
    else{
        for(int i = 0 ; i < a_size; i++){
            long long c = 0;
            for(int j = 0; j < b_size; j++){
                res[i+j] += a[i]*b[j]+c;
                c = res[i+j]/base;
                res[i+j] %= base;
            }
            if(c){
                res[i+b_size]+=c;
            }
        }
    }
    while(!res.empty() && res.back() == 0){
        res.pop_back();
    }
    return res;
}

void print(std::vector<long long> res, long long width) {
    std::cout << "size :" << res.size() << std::endl;
    std::cout << res.back();
    for(int i = res.size()-2; i >=0; i--){
        std::cout <<std::setw(width) << std::setfill('0') << res[i];
    }
    std::cout << std::endl;
}
