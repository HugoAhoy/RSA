// util.hpp
#ifndef UTIL_HPP
#define UTIL_HPP
#include "Int.hpp"

Int Random_Nbits_Int(long long nbits);

Int Random_Nbits_Prime(long long nbits);

bool Miller_Rabin(const Int &b);

#endif