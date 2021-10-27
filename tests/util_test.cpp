#include "Int.hpp"
#include "string"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "util.hpp"

TEST(utilTest, RandomNbitInt){
    Int b31 = Int(1ll<<31);
    Int b32 = Int(1ll<<32);
    Int b63 = b31*b32;
    Int b64 = b32*b32;
    Int b127 = b64*b63;
    Int b128 = b64*b64;
    Int b255 = b128*b127;
    Int b256 = b128*b128;
    Int b511 = b256*b255;
    Int b512 = b256*b256;
    Int b767 = b512*b255;
    Int b768 = b512*b256;
    Int b1023 = b512*b511;
    Int b1024 = b512*b512;
    Int b2047 = b1024*b1023;
    Int b2048 = b1024*b1024;
    Int b4095 = b2048*b2047;
    Int b4096 = b2048*b2048;
    EXPECT_THAT(Random_Nbits_Int(64),::testing::AllOf(::testing::Lt(b64),::testing::Ge(b63)));
    EXPECT_THAT(Random_Nbits_Int(128),::testing::AllOf(::testing::Lt(b128),::testing::Ge(b127)));
    EXPECT_THAT(Random_Nbits_Int(256),::testing::AllOf(::testing::Lt(b256),::testing::Ge(b255)));
    EXPECT_THAT(Random_Nbits_Int(512),::testing::AllOf(::testing::Lt(b512),::testing::Ge(b511)));
    EXPECT_THAT(Random_Nbits_Int(768),::testing::AllOf(::testing::Lt(b768),::testing::Ge(b767)));
    EXPECT_THAT(Random_Nbits_Int(1024),::testing::AllOf(::testing::Lt(b1024),::testing::Ge(b1023)));
    EXPECT_THAT(Random_Nbits_Int(2048),::testing::AllOf(::testing::Lt(b2048),::testing::Ge(b2047)));
    EXPECT_THAT(Random_Nbits_Int(4096),::testing::AllOf(::testing::Lt(b4096),::testing::Ge(b4095)));
}