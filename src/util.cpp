#include "random"
#include "util.hpp"
#include "Int.hpp"
#include "iostream"

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
    // std::cout << num << std::endl;
    long long temp = num % (1ll<<last) | (1ll<<(last-1));
    // std::cout << temp << std::endl;
    Int ans(temp);
    for (int i = 0; i < parts; i++){
        ans = ans*base+Int(dist(mt));
    }
    return ans;
}