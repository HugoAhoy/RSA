// RSA.hpp
#ifndef RSA_HPP
#define RSA_HPP
#include "Int.hpp"
#include "string"

struct Keys{
    Int n;
    Int e; // 公钥
    Int d; // 私钥
    Keys(const Int &_n, const Int &_e, const Int &_d);
};

Keys GenerateKey(long long key_length);

Int Encrypt(const Int &PublicKey_e, const Int &PublicKey_n, Int Content);

Int Decrypt(const Int &PrivateKey, const Int &PublicKey_n, Int Content);

#endif