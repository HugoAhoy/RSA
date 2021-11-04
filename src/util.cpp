#include "random"
#include "util.hpp"
#include "Int.hpp"
#include "iostream"
#include "vector"

// 100% 判定long long 的一组基。
std::vector<long long> test_num({2,325,9375,28178,450775,9780504,1795265022});

static std::vector<Int> big_test_num({Random_Nbits_Int(20),Random_Nbits_Int(40),Random_Nbits_Int(60),Random_Nbits_Int(80),Random_Nbits_Int(100),Random_Nbits_Int(120)});

Int Random_Nbits_Int(long long nbits) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<long long> dist(0, (1ll<<32) - 1);
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
    Int odd_1 = Random_Nbits_Int(nbits);
    Int odd_2;
    Int res;
    while(true){
        odd_1 = Random_Nbits_Int(nbits);
        
        if(!odd_1.is_odd()){
            odd_1 = odd_1 + 1;
        }
        
        // 构造6k+1和6k-1
        long long odd_mod3 = odd_1.mod3();
        if(!odd_mod3){
            odd_1 = odd_1+2;// TODO: 可能导致odd的#bit = nbits+1
            odd_2 = odd_1+2;
        }
        else if(odd_mod3 == 1){
            odd_2 = odd_1 - 2;
        }
        else{
            odd_2 = odd_1 + 2;
        }

        if(Miller_Rabin(odd_1)){
            return odd_1;
        }
        if(Miller_Rabin(odd_2)){
            return odd_2;
        }

        for(long long i = 1; i < nbits/6; i++){
            res = odd_1 + i*6;
            if(Miller_Rabin(res)){
                return res;
            }
            res = odd_1 - i*6;
            if(Miller_Rabin(res)){
                return res;
            }
            res = odd_2 + i*6;
            if(Miller_Rabin(res)){
                return res;
            }
            res = odd_2 - i*6;
            if(Miller_Rabin(res)){
                return res;
            }
        }
        return res;
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

    // base test
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
    for(long long i = 0; i < base_num; i++){
        Int res = big_test_num[i].power(m, b);
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

Int EX_GCD(const Int &a, const Int &b, Int &x, Int &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    Int q = a/b;
    Int res = EX_GCD(b, a - q*b,  x, y);
    Int temp = y;
    y = x - q*y;
    x = temp;
    return res;
}