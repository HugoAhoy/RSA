// Int.hpp
#ifndef RSA_HPP
#define RSA_HPP
#include "Int.hpp"
#include "string"

std::pair<Int, Int> GenerateKey(Int KeyLength);

Int Encrypty(Int PublicKey, Int Content);

Int Decrypty(Int PrivateKey);

#endif