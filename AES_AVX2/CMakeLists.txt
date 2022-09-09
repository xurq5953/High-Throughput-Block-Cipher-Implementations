cmake_minimum_required(VERSION 3.0)
project(AES_AVX2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-mavx2 -m64 -Ofast -funroll-loops -flto  ${CMAKE_CXX_FLAGS}")
add_executable(AES_AVX2 main.cpp sbox.cpp transpose3.cpp data.cpp mixlinear2.cpp key_expansion.cpp)
