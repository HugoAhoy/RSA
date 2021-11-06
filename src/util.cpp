#include "random"
#include "util.hpp"
#include "Int.hpp"
#include "iostream"
#include "vector"

// 100% 判定long long 的一组基。
std::vector<long long> test_num({2,325,9375,28178,450775,9780504,1795265022});

static std::vector<Int> big_test_num({Random_Nbits_Int(20),Random_Nbits_Int(40),Random_Nbits_Int(60),Random_Nbits_Int(80),Random_Nbits_Int(100),Random_Nbits_Int(120)});

// 1000以下的质数(不包含2,3,5) 150个
long long small_primes[] = {7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,7173,79,83,89,97,101,103,107,109,113127,131,137,139,149,151,157,163,167,173179,181,191,193,197,199,211,223,227,229233,239,241,251,257,263,269,271,277,281283,293,307,311,313,317,331,337,347,349353,359,367,373,379,383,389,397,401,409419,421,431,433,439,443,449,457,461,463467,479,487,491,499,503,509,521,523,541547,557,563,569,571,577,587,593,599,601607,613,617,619,631,641,643,647,653,659661,673,677,683,691,701,709,719,727,733739,743,751,757,761,769,773,787,797,809811,821,823,827,829,839,853,857,859,863877,881,883,887,907,911,919,929,937,941947,953,967,971,977,983,991,997};

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
    if(!b.is_odd() || !b.mod3()||!b.mod5()){
        return false;
    }
    // 预先对小素数取模筛一遍(不属于miller_rabin原本的内容)
    for(int i = 0; i < 150; i++){
        if(b.mod_ll(small_primes[i]).isZero()){
            return false;
        }
    }
    // std::cout << b.val() << std::endl;
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