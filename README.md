# RSA C++ Implementation

This repository is the C++ implementation of classical RSA algorithm. Some novel and effective optimization algorithms are applied to speed up the Key Generation, Encryption and Descryption.

The project is for recording the process of the course work of Applied Cryptography.

## test

We use `gtest` to test.

Make sure you are at the root directory where the `CMakeLists.txt` is.

Run these commands:

```sh
cmake -S . -B build
cmake --build build
cd build
ctest
```
