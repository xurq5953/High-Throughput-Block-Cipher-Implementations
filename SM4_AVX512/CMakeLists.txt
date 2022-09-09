project ("SM4_AVX512")
cmake_minimum_required (VERSION 3.5)

set(CMAKE_CXX_FLAGS "-mavx512f -mavx512cd -m64 -march=skylake-avx512 -Ofast -funroll-loops -flto ${CMAKE_CXX_FLAGS}")

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME}  main.cpp data.cpp encryptool.h key_expansion.cpp linerLayer.cpp transpose.cpp transpose2.cpp sbox4.cpp sbox.cpp sbox5.cpp sbox6.cpp linearnew.cpp mixlinear.cpp)


