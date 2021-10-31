#include "random"
#include "util.hpp"
#include "Int.hpp"
#include "iostream"
#include "vector"

// 100% 判定long long 的一组基。
std::vector<long long> test_num({2,325,9375,28178,450775,9780504,1795265022});

Int Random_Nbits_Int(long long nbits) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<long long> dist(0, (1ll<<32) - 1);
    Int base = Int(1ll<<32);
    long long parts = nbits/32;
    long long last = nbits%32;
    if(last == 0){
        parts -= 1;
        last = 32;
    }
    long long num = dist(mt);
    long long temp = num % (1ll<<last) | (1ll<<(last-1));
    Int ans(temp);
    for (int i = 0; i < parts; i++){
        ans = ans*base+Int(dist(mt));
    }
    return ans;
}

Int Random_Nbits_Prime(long long nbits){
    Int odd = Random_Nbits_Int(nbits);
    while(true){
        if(!odd.is_odd()){
            odd = odd + 1;
        }
        if(!odd.mod3()){
            odd = odd+2;// TODO: 可能导致odd的#bit = nbits+1
        }
        if(Miller_Rabin(odd)){
            return odd;
        }
        odd = Random_Nbits_Int(nbits);
    }
}

bool Miller_Rabin(const Int &b){
    if(!b.is_odd() || !b.mod3()){
        return false;
    }
    Int m = b-1;
    Int pos_one(1), neg_one(m);
    long long t = 0;
    while(!m.is_odd()){
        m.rightshift();
        t++;
    }

    // bast test
    for(int i = 0; i < 7; i++){
        Int res = Int(test_num[i]).power(m, b);
        if(res == pos_one || res == neg_one){
            continue;
        }

        for(int j = 1;j <= t; j++){
            res = (res*res)%b;
            if(res==neg_one && j != t){
                res=pos_one;
                break;
            }
            else if(res==pos_one){
                return false;
            }
        }
        if(!(res==pos_one)){
            return false;
        }
    }

    // extra test
    long long base_num = b.length()/50;
    for(long long i = 1; i < base_num; i++){
        Int res = Random_Nbits_Int(i*20).power(m, b);
        if(res == pos_one || res == neg_one){
            continue;
        }

        for(int j = 1;j <= t; j++){
            res = (res*res)%b;
            if(res==neg_one && j != t){
                res=pos_one;
                break;
            }
            else if(res==pos_one){
                return false;
            }
        }
        if(!(res==pos_one)){
            return false;
        }        
    }
    return true;
}