cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11" )
project(RSA C CXX)

# For GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)
message(status "Project Directory: ${PROJECT_SOURCE_DIR}")
add_compile_options(-std=c++11)
add_executable(
  demo
  main_test.cpp
  src/Int.cpp
  src/util.cpp
)
enable_testing()

add_executable(
  Int_test
  tests/Int_test.cpp
  src/Int.cpp
)
add_executable(
  util_test
  tests/util_test.cpp
  src/Int.cpp
  src/util.cpp
)
target_link_libraries(
  Int_test
  gtest_main
)
target_link_libraries(
  util_test
  gmock_main
)

include(GoogleTest)
gtest_discover_tests(Int_test)