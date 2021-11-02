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

Int Encrypty(Int PublicKey, Int Content);

Int Decrypty(Int PrivateKey);

#endif