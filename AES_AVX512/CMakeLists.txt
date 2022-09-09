cmake_minimum_required(VERSION 3.10)
project(AES_AVX512)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-mavx512f -mavx512cd -m64 -march=skylake-avx512 -Ofast -funroll-loops -flto ${CMAKE_CXX_FLAGS}")

add_executable (${PROJECT_NAME}  main.cpp data.cpp encryptool.h key_expansion.cpp transpose2.cpp sbox2.cpp  mixlinear2.cpp)