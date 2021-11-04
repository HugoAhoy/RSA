#include "Int.hpp"
#include "string"
#include "RSA.hpp"
#include "util.hpp"
#include "iostream"

Keys::Keys(const Int &_n, const Int &_e, const Int &_d){
    this->n = _n;
    this->e = _e;
    this->d = _d;
}

Keys GenerateKey(long long key_length){
    Int p = Random_Nbits_Prime(key_length>>1);
    Int q = Random_Nbits_Prime(key_length - (key_length>>1));
    Int n = p*q;
    std::cout << p.val() << std::endl;
    std::cout << q.val() << std::endl;
    Int phi_n = n - p -q +1;// (p-1)(q-1) = pq-p-q+1
    // 生成公钥(常见的将e固定为最大的费马数65537)
    Int e = 65537;
    // 生成私钥
    Int x, d;
    std::cout << EX_GCD(phi_n, e, x, d).val() << std::endl;
    std::cout << d.val() << std::endl;
    while(d < 0){
        d = d+phi_n;
    }
    return Keys(n, e, d);
}

Int Encrypt(const Int &PublicKey_e, const Int &PublicKey_n,  Int Content){
    return Content.power(PublicKey_e, PublicKey_n);
}

Int Decrypt(const Int &PrivateKey, const Int &PublicKey_n, Int Content){
    return Content.power(PrivateKey, PublicKey_n);
}
