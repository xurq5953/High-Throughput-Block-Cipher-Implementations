//Version 1.0
#ifndef ENCRYPTOOL_LIBRARY_H
#define ENCRYPTOOL_LIBRARY_H

#include <cstdint>
#include <iostream>
//#include <windows.h>
#include <x86intrin.h>
#include <string.h>


static inline __m128i SHL128(__m128i v, int n) 
{ 
    __m128i v1, v2; 
 
    if ((n) >= 64) 
    { 
        v1 = _mm_slli_si128(v, 8); 
        v1 = _mm_slli_epi64(v1, (n) - 64);
    } 
    else 
    { 
        v1 = _mm_slli_epi64(v, n); 
        v2 = _mm_slli_si128(v, 8); 
        v2 = _mm_srli_epi64(v2, 64 - (n)); 
        v1 = _mm_or_si128(v1, v2); 
    } 
    return v1; 
}


static inline __m128i SHR128(__m128i v, int n)
{ 
    __m128i v1, v2; 
 
    if (n >= 64) 
    { 
        v1 = _mm_srli_si128(v, 8); 
        v1 = _mm_srli_epi64(v1, n - 64); 
    } 
    else 
    { 
        v1 = _mm_srli_epi64(v, n); 
        v2 = _mm_srli_si128(v, 8); 
        v2 = _mm_slli_epi64(v2, 64 - (n)); 
        v1 = _mm_or_si128(v1, v2); 
    } 
    return v1; 
}
template<typename T>
static inline void print_by_bit(T num) {
    size_t n = sizeof(T) * 8;
    for (int i = 0; i < n; ++i) {
        printf("%d", (num >> (n - 1 - i)) & 1);
        if (i != 0 && i % 8 == 0) std::cout << " ";
    }

    printf("\n");
}


static inline void load_8_in_64(uint64_t *u64, const uint8_t *u8) {
    *u64 = (uint64_t) u8[0] << 56 |
           (uint64_t) u8[1] << 48 |
           (uint64_t) u8[2] << 40 |
           (uint64_t) u8[3] << 32 |
           (uint64_t) u8[4] << 24 |
           (uint64_t) u8[5] << 16 |
           (uint64_t) u8[6] << 8 |
           (uint64_t) u8[7];
}

static inline void load_8_in_64_reverse(uint64_t *u64, const uint8_t *u8) {
    *u64 = (uint64_t) u8[0] |
           (uint64_t) u8[1] << 8 |
           (uint64_t) u8[2] << 16 |
           (uint64_t) u8[3] << 24 |
           (uint64_t) u8[4] << 32 |
           (uint64_t) u8[5] << 40 |
           (uint64_t) u8[6] << 48 |
           (uint64_t) u8[7] << 56;
}

static inline void load_8_in_32(uint32_t *u32, const uint8_t *u8) {
    *u32 = (uint32_t) u8[0] << 24 |
           (uint32_t) u8[1] << 16 |
           (uint32_t) u8[2] << 8 |
           (uint32_t) u8[3];
}

static inline void store_64_in_8_reverse(uint8_t *u8, const uint64_t *u64) {
    u8[0] = (uint8_t) *u64 ;
    u8[1] = (uint8_t) (*u64 >> 8);
    u8[2] = (uint8_t) (*u64 >> 16);
    u8[3] = (uint8_t) (*u64 >> 24);
    u8[4] = (uint8_t) (*u64 >> 32);
    u8[5] = (uint8_t) (*u64 >> 40);
    u8[6] = (uint8_t) (*u64 >> 48);
    u8[7] = (uint8_t) (*u64 >> 56);
}

static inline void store_64_in_8(uint8_t* u8, const uint64_t* u64) {
    u8[0] = (uint8_t)(*u64 >> 56);
    u8[1] = (uint8_t)(*u64 >> 48);
    u8[2] = (uint8_t)(*u64 >> 40);
    u8[3] = (uint8_t)(*u64 >> 32);
    u8[4] = (uint8_t)(*u64 >> 24);
    u8[5] = (uint8_t)(*u64 >> 16);
    u8[6] = (uint8_t)(*u64 >> 8);
    u8[7] = (uint8_t)*u64;
}

static inline void store_32_in_8(uint8_t *u8, const uint32_t *u32) {
    u8[0] = (uint8_t) (*u32 >> 24);
    u8[1] = (uint8_t) (*u32 >> 16);
    u8[2] = (uint8_t) (*u32 >> 8);
    u8[3] = (uint8_t) *u32;
}

typedef unsigned long long int64;

inline int64 GetCycleCount()
{
    int64 hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (int64)lo)|( ((int64)hi)<<32 );
}


static int64 ticks_start, ticks_end;

static inline void startCycles()
{
    ticks_start = GetCycleCount();
}

// unit: cycles
static inline int64 stopCycles()
{
    ticks_end = GetCycleCount();
    return (ticks_end - ticks_start);
}

static inline int64 stopWithPrintCycles()
{
    int64 cycles;
    ticks_end = GetCycleCount();
    cycles = (ticks_end - ticks_start);
    printf("\n----------Elapsed Timing(Cycles) : %llu\n", cycles);
    printf("----------------------------------------\n");

    return cycles;
}



//#define timing_t double
//static _LARGE_INTEGER time_start, time_over;
//static double dqFreq;
//
//
//static inline void start_timing() {
//    _LARGE_INTEGER f;
//    QueryPerformanceFrequency(&f);
//    dqFreq = (double) f.QuadPart;
//
//    QueryPerformanceCounter(&time_start);
//}
//
//// unit: ms
//static inline timing_t stop_timing() {
//    QueryPerformanceCounter(&time_over);
//    return ((double) (time_over.QuadPart - time_start.QuadPart) / dqFreq * 1000);
//}
//
//
////Mb/s
//static inline void print_speed(long Mbits) {
//    timing_t timing = stop_timing();
//    double speed = (Mbits / (timing / 1000));
//    std::cout << std::endl << Mbits << "M bits idata" << std::endl;
//    std::cout << "Run for :" << timing / 1000 << "s " << std::endl;
//    std::cout << "The speed is :" << speed  << "Mb/s " << std::endl;
//    //* 1.094
//}


static void print128_num(const __m128i var)
{
    uint8_t val[16];
    memcpy(val, &var, sizeof(val));
    printf("Numerical: %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x %#x\n",
        val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], val[9], val[10], val[11], val[12], val[13], val[14], val[15]);
}
using namespace std;
static void print256_num(string c, const __m256i var)
{
    
    uint8_t val[32];
    memcpy(val, &var, sizeof(val));
    cout << c << " : ";
    for (size_t i = 0; i < 32; i++)
        printf("%#x ",val[i]);
    printf("\n");
}

#endif //ENCRYPTOOL_LIBRARY_H
