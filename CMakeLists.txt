cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
project(RSA C CXX)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized -Wno-error=unused-parameter")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wno-error=maybe-uninitialized")
# For GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.6.0.zip
)

FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

include_directories(${PROJECT_SOURCE_DIR}/include)
message(status "Project Directory: ${PROJECT_SOURCE_DIR}")
message("Build Type: ${CMAKE_BUILD_TYPE}")
add_compile_options(-std=c++11)

add_executable(
  RSA
  src/main_rsa.cpp
  src/Int.cpp
  src/util.cpp
  src/Karatsuba.cpp
  src/RSA.cpp
)
enable_testing()

add_executable(
  Int_test
  tests/Int_test.cpp
  src/Int.cpp
  src/Karatsuba.cpp
)
add_executable(
  util_test
  tests/util_test.cpp
  src/Int.cpp
  src/util.cpp
  src/Karatsuba.cpp
)

add_executable(
  Int_bench
  benchmarks/Int_bench.cpp
  src/Int.cpp
  src/util.cpp
  src/Karatsuba.cpp
)

add_executable(
  util_bench
  benchmarks/util_bench.cpp
  src/util.cpp
  src/Int.cpp
  src/Karatsuba.cpp
)

add_executable(
  RSA_bench
  benchmarks/RSA_bench.cpp
  src/util.cpp
  src/Int.cpp
  src/Karatsuba.cpp
  src/RSA.cpp
)

target_link_libraries(
  Int_test
  gtest_main
)
target_link_libraries(
  util_test
  gmock_main
)
target_link_libraries(
  Int_bench
  benchmark_main
)

target_link_libraries(
  util_bench
  benchmark_main
)

target_link_libraries(
  RSA_bench
  benchmark_main
)

include(GoogleTest)
gtest_discover_tests(Int_test)