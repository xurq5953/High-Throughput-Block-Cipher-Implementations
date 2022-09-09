project ("SM4_AVX2")
cmake_minimum_required (VERSION 3.8)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -m64 -O3 ")
set(CMAKE_CXX_FLAGS "-mavx2 -m64  -Ofast -funroll-loops -flto  ${CMAKE_CXX_FLAGS}")

add_executable (${PROJECT_NAME} main.cpp data.cpp  encryptool.h key_expansion.cpp transpose.cpp linerLayer.cpp  transpose.cpp sbox.cpp sbox2.cpp sbox3.cpp sbox4.cpp sbox5.cpp)


