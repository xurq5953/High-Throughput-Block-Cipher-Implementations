#include <iostream>
#include <x86intrin.h>
#include <string>
#include "encryptool.h"
#include <ctime>

using namespace std;

alignas(64) extern uint8_t text[];

__m512i *bundle;

extern uint32_t roundkey[32];

__m512i new_x[32];

void sbox5(__m512i *b);

void sbox6(__m512i *b);

void mixlinear(__m512i *x, __m512i *bundle);

void key_expansion();

inline void output_text();

void transpose_simultaneously(__m512i *A);

#define V(a, b, c, d) _mm512_ternarylogic_epi32((a), (b), (c), (d))

uint8_t *idata;
__m512i mask_load;
__m512i mask_store;
alignas(64) extern uint8_t load_mask_list[64];
alignas(64) extern uint8_t store_mask_list[64];

void init_data() {
    idata = (uint8_t *) aligned_alloc(64, 8192);
    memcpy(idata, text, 4096);
    memcpy(&idata[4096], text, 4096);
    bundle = (__m512i *) idata;
    mask_load = _mm512_load_si512(load_mask_list);
    mask_store = _mm512_load_si512(store_mask_list);
}


inline void format_bundle() {
    for (int i = 0; i < 128; ++i)
        bundle[i] = _mm512_shuffle_epi8(bundle[i], mask_load);
    transpose_simultaneously(bundle);
}

inline void output_text() {
    transpose_simultaneously(bundle);
    for (int i = 0; i < 128; ++i)
        bundle[i] = _mm512_shuffle_epi8(bundle[i], mask_store);
}


void encrypt() {
    int index0, index1, index2, index3;
    uint32_t key;
    for (int round = 0; round < 32; ++round) {
        index0 = (round % 4) * 32;
        index1 = (index0 + 32) % 128;
        index2 = (index0 + 64) % 128;
        index3 = (index0 + 96) % 128;
        key = roundkey[round];

        for (int i = 0; i < 32; ++i) {
            new_x[i] = V(bundle[index1 + i], bundle[index2 + i], bundle[index3 + i], 0x96);
            new_x[i] = new_x[i] ^ _mm512_set1_epi32(-((key >> i) & 1));
        }

        //S-box
        sbox5(new_x);
        sbox5(new_x + 8);
        sbox5(new_x + 16);
        sbox5(new_x + 24);

        mixlinear(new_x, bundle + index0);

    }
}

int main() {
    init_data();
    key_expansion();
    format_bundle();
    encrypt();
    output_text();

    unsigned long long time = 0x200000;

    unsigned long long Mbits = (time >> 4); //  (>>20) * 512 * 128
    clock_t start, end;
    start = clock();
    for (long i = 0; i < time; ++i) {
        encrypt();
    }
    end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    double speed_time = Mbits / elapsed;
    printf("\n----------Elapsed Timing is %f\n Encrypt speed is %f Mb/s\n", elapsed, speed_time);

    unsigned long long bytes = time << 13;
    startCycles();
    for (long i = 0; i < time; ++i)
        encrypt();
    unsigned long long cycles = stopWithPrintCycles();
    printf("Encrypt speed is %f cycles/bytes\n", (double) cycles / bytes);



    free(idata);
    return 0;
}
